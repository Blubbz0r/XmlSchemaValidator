#include <gmock/gmock.h>

#include "XmlSchemaValidator.h"

using namespace testing;
using namespace XSV;

class XmlSchemaValidatorTest : public Test
{
public:
    XmlSchemaValidator validatorWithValidXsd{QUrl{ValidXsdPath}};

    static const QString ValidXsdPath;
    static const QString ValidXmlPath;
    static const QString InvalidXmlPath;
};

const QString XmlSchemaValidatorTest::ValidXsdPath = "qrc:/Files/SchemaXsd";
const QString XmlSchemaValidatorTest::ValidXmlPath = "qrc:/Files/ValidXml";
const QString XmlSchemaValidatorTest::InvalidXmlPath = "qrc:/Files/InvalidXml";

TEST_F(XmlSchemaValidatorTest, validate_WithoutSchemaPath_ThrowsException)
{
    XmlSchemaValidator validator;
    ASSERT_THROW(validator.validate(ValidXmlPath), std::logic_error);
}

TEST_F(XmlSchemaValidatorTest, validate_WithInvalidSchema_ReturnsFalse)
{
    XmlSchemaValidator validator{QUrl(ValidXmlPath)};
    ASSERT_FALSE(validator.validate(ValidXmlPath));
}

TEST_F(XmlSchemaValidatorTest, validate_WithValidXsdAndXml_ReturnsTrue)
{
    ASSERT_TRUE(validatorWithValidXsd.validate(ValidXmlPath));
}

TEST_F(XmlSchemaValidatorTest, validate_WithValidXsdAndInvalidXml_ReturnsFalse)
{
    ASSERT_FALSE(validatorWithValidXsd.validate(InvalidXmlPath));
}
