#ifndef SCENE_HPP
#define SCENE_HPP

#include "gui/gui_object.hpp"

namespace lgc
{
class Scene
{
public:

	void draw();
	
	void interact();

private:
    std::vector<gui::GUIObject> m_gui_objects;
};
} // namespace lgc

#endif // SCENE_HPP