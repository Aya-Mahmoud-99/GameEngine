#ifndef OUR_UTILS_IMGUI_H
#define OUR_UTILS_IMGUI_H

//#include <functional>
//#include <iterator>
//#include <optional>
#include <map>
//#include <iterator>
//#include <type_traits>

#include <glad/gl.h>
#include "string.h"
//#include <imgui.h>
//#include <glm/common.hpp>

//namespace our {

    namespace enum_options {
        typedef std::map<std::string, GLenum>  EnumMap;

        inline EnumMap dpFunc = {
                {"GL_LEQUAL", GL_LEQUAL},
        };
        inline EnumMap cullface = {
                {"GL_BACK", GL_BACK},
        };
        inline EnumMap frontwinding = {
                {"GL_CCW", GL_CCW},
        };

        inline EnumMap blendFun = {
                {"GL_FUNC_ADD", GL_FUNC_ADD},
        };

        inline EnumMap source = {
                {"GL_SRC_ALPHA", GL_SRC_ALPHA},
        };

        inline EnumMap dest = {
                {"GL_ONE_MINUS_SRC_ALPHA", GL_ONE_MINUS_SRC_ALPHA},
        };

    }
//}
#endif //OUR_UTILS_IMGUI_H
