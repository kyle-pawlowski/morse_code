#include <wiringPi.h>
#include <unistd.h>
#include <chrono>
#include <cmath>
#include <stdlib.h>
#include <unordered_map>
#include <iostream> 

std::unordered_map<char,char> map (36);

//base time unit in ms
int base = 250;
int mintime = 10;
int pin = 12;
int current_state = 0;

void make_key(std::unordered_map<char,char> *ref){
    std::pair<char,char> A_m (7,'A');
    ref->insert(A_m);
    std::pair<char,char> B_m (41, 'B');
    ref->insert(B_m);
    std::pair<char,char> C_m(50, 'C');
    ref->insert(C_m);
    std::pair<char,char> D_m(14, 'D');
    ref->insert(D_m);
    std::pair<char,char> E_m(1, 'E');
    ref->insert(E_m);
    std::pair<char,char> F_m(49, 'F');
    ref->insert(F_m);
    std::pair<char,char> G_m(17, 'G');
    ref->insert(G_m);
    std::pair<char,char> H_m(40, 'H');
    ref->insert(H_m);
    std::pair<char,char> I_m(4, 'I');
    ref->insert(I_m);
    std::pair<char,char> J_m(79, 'J');
    ref->insert(J_m);
    std::pair<char,char> K_m(23, 'K');
    ref->insert(K_m);
    std::pair<char,char> L_m(43, 'L');
    ref->insert(L_m);
    std::pair<char,char> M_m(8, 'M');
    ref->insert(M_m);
    std::pair<char,char> N_m(5, 'N');
    ref->insert(N_m);
    std::pair<char,char> O_m(26, 'O');
    ref->insert(O_m);
    std::pair<char,char> P_m(52, 'P');
    ref->insert(P_m);
    std::pair<char,char> Q_m(71, 'Q');
    ref->insert(Q_m);
    std::pair<char,char> R_m(16, 'R');
    ref->insert(R_m);
    std::pair<char,char> S_m(13, 'S');
    ref->insert(S_m);
    std::pair<char,char> T_m(2, 'T');
    ref->insert(T_m);
    std::pair<char,char> U_m(22, 'U');
    ref->insert(U_m);
    std::pair<char,char> V_m(67, 'V');
    ref->insert(V_m);
    std::pair<char,char> W_m(25, 'W');
    ref->insert(W_m);
    std::pair<char,char> X_m(68, 'X');
    ref->insert(X_m);
    std::pair<char,char> Y_m(77, 'Y');
    ref->insert(Y_m);
    std::pair<char,char> Z_m(50, 'Z');
    ref->insert(Z_m);
}

void init(){
    wiringPiSetup();
    pinMode(pin,INPUT);
    make_key(&map);
}

int waitForStateChange(){
    //returns time gpio pin is either high or low
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    while(digitalRead(pin) == current_state){
        usleep(5);
    }
    current_state = digitalRead(pin);
    std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();
    int duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    return duration;
}

char letterInterpret() throw(char){
    // dots and dashes are interpreted as trinary numbers where:
    // 0 is nothing
    // 1 is a dot
    // 2 is a dash
    unsigned char letter = 0;
    for(int i = 0; i<8; i++){
        int state = current_state;
        int duration = waitForStateChange();
        if(state == 1){
            if(duration/base >= 2){
                letter += 2*pow(3,i);
            }
            else{
                letter += pow(3,i);
            }
        }
        else{
            if(duration/base < 2){
                i--;
                continue;
            }
            else if(duration/base > 5){
                throw letter;
            }
            else{
                return letter;
            }
        }
    }
    return letter;
}

char morse2char(char code){
    char letter = map.at(code);
    return letter;
}

void read(){
    char letter;
    while(1){
        try{
            letter = letterInterpret();
            letter = morse2char(letter);
        }
        catch(char e){
            std::cout<<' '<<std::endl;
            letter = e;
        }
        std::cout<<letter<<std::endl;
    }
}
//char morse2ascii(char num){

//}

int main(){
    init();
    read();
    return 0;
}
