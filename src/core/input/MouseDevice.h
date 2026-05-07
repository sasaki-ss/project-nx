#ifndef CORE_INPUT_MOUSEDEVICE_H
#define CORE_INPUT_MOUSEDEVICE_H

#include <unordered_map>

namespace nx {
namespace core {
namespace input {

class MouseDevice {
public:
	MouseDevice() = default;
	~MouseDevice() = default;
	bool init();
	void update();
private:

};

}
}
}

#endif // CORE_INPUT_MOUSEDEVICE_H
