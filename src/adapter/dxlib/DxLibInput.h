#ifndef ADAPTER_DXLIB_DXLIBINPUT_H
#define ADAPTER_DXLIB_DXLIBINPUT_H

#include <array>

#include "core/InputBase.h"

namespace adapter {
namespace dxlib {

class DxLibInput final : public nx::core::input::InputBase {
public:
	DxLibInput() = default;
	~DxLibInput()override = default;
	bool init()override;
	void update()override;
private:
	void update_key_state(nx::core::input::Key key, int state);
};

}
}

#endif // !ADAPTER_DXLIB_DXLIBINPUT_H
