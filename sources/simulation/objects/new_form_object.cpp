#include "new_form_object.hpp"

sml::NewFormObject::NewFormObject(bool is_const)
    : BaseObject(FormType::NEW)
{
}

void
sml::NewFormObject::addBorder(BaseBorderPtr&& b)
{
    BaseObject::addBorder(std::move(b));
}