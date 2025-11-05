#ifndef CONKEY_INTERPRET_VALUES_HPP
#define CONKEY_INTERPRET_VALUES_HPP

#include <cstdint>
#include <string>
#include <memory>

namespace Conkey::Interpret {

    enum class ValueType {
        INTEGER_VALUE, BOOLEAN_VALUE, NULL_VALUE
    };

    struct Value {
        virtual ~Value() = default;

        virtual ValueType   valueType() = 0;
        virtual std::string inspect() = 0;
    };

    using ValuePtr = std::shared_ptr<Conkey::Interpret::Value>;

    struct IntegerValue : public Value {
        ValueType valueType() override;
        std::string inspect() override;

        std::int64_t value_;
    };

    struct BooleanValue : public Value {
        ValueType valueType() override;
        std::string inspect() override;

        bool value_;
    };

    struct NullValue : public Value {
        ValueType valueType() override;
        std::string inspect() override;
    };

}

#endif // CONKEY_INTERPRET_VALUES_HPP
