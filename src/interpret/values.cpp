#include "conkey/interpret/values.hpp"
#include <string>


namespace Conkey::Interpret {

    ValueType IntegerValue::valueType() {
        return ValueType::INTEGER_VALUE;
    }

    std::string IntegerValue::inspect() {
        return std::to_string(this->value_);
    }

    ValueType BooleanValue::valueType() {
        return ValueType::BOOLEAN_VALUE;
    }

    std::string BooleanValue::inspect() {
        return this->value_ ? "true" : "false";
    }

    ValueType NullValue::valueType() {
        return ValueType::NULL_VALUE;
    }

    std::string NullValue::inspect() {
        return "null";
    }

}
