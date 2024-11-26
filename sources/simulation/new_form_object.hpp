#ifndef UPDATABLE_OBJECT_HPP
#define UPDATABLE_OBJECT_HPP

#include "base_object.hpp"

namespace sml
{
class NewFormObject : public BaseObject
{
public:
    NewFormObject();

    bool addBorder(BaseBorderPtr&& b);

private:
};
} // namespace sml
#endif // !UPDATABLE_OBJECT_HPP