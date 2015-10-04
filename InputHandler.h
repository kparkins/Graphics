#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <functional>
#include <unordered_map>

#include "Globals.h"

using std::function;
using std::unordered_map;
using std::placeholders::_1;

typedef struct InputData {
    float data[4];
}InputData;

typedef function<void(InputData)> KeyHandler;

class InputHandler {

public:
    
    InputHandler();
    ~InputHandler();

    void handle(char key, InputData);

private:

    void toggleSpin(InputData & input);
    void toggleShowSphere(InputData & input);
   
    void translatePositiveX(InputData & input);
    void translateNegativeX(InputData & input);
    void translatePositiveY(InputData & input);
    void translateNegativeY(InputData & input);
    void translatePositiveZ(InputData & input);
    void translateNegativeZ(InputData & input);

    void reset(InputData & input);
    void scaleUp(InputData & input);
    void scaleDown(InputData & input);
    void orbitClockwiseZ(InputData & input);
    void orbitCounterZ(InputData & input);

    unordered_map<char, KeyHandler> m_keyMap;

};

#endif