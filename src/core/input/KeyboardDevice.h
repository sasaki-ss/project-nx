#ifndef CORE_INPUT_KEYBOARDDEVICE_H
#define CORE_INPUT_KEYBOARDDEVICE_H

#include <unordered_map>

namespace nx {
namespace core {
namespace input {

class KeyboardDevice {
public:
	KeyboardDevice() = default;
	~KeyboardDevice() = default;
	bool init();
	void update();
private:

};

}
}
}

#endif // CORE_INPUT_KEYBOARDDEVICE_H
