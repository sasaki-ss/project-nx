#ifndef CORE_OBJECT_COMPONENT
#define CORE_OBJECT_COMPONENT

#include "InputSystem.h"

namespace nx {
namespace core {
namespace object {

class Component final {
public:
	Component() = default;
	~Component() = default;
	auto input() -> input::InputSystem& {
		return input_system;
	}
private:
	input::InputSystem input_system;
};


}
}
}

#endif // !CORE_OBJECT_COMPONENT
