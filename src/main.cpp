//#if defined(WIN32)
//    #include <windows.h>
//#endif
//
//#include "Runner.hpp"
//
//#ifdef CONSOLE
//int main()
//#elif WIN32
//int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevIns, LPSTR lpszArgument, int iShow)
//#endif
//{
//    Runner runner;
//    try {
//        runner.run();
//    }
//    catch (...) {
//
//    }
//    return 0;
//}
//

#include <unordered_map>
#include <vector>

#include <inih/INIReader.h>
#include <robot2D/Util/Logger.h>
#include <robot2D/Util/ResourceHandler.h>
#include <robot2D/Graphics/Texture.h>
#include <robot2D/Graphics/Font.h>

const std::string resourceiniPath = "res/config.ini";


enum class ResourceID {
    Audio,
    Font,
    Level,
    Texture,
    Shader
};

struct ResourceConfiguration {
    mutable std::string audioDir;
    mutable std::string fontDir;
    mutable std::string levelDir;
    mutable std::string textureDir;
    mutable std::string shaderDir;
};

struct GameConfiguration {
    mutable float speed;
    mutable float ball_radius;
    mutable unsigned int max_lives;
    mutable unsigned int emitter_new_sz;
    mutable robot2D::vec2f ball_velocity;
    mutable robot2D::vec2f paddle_size;
};

class Configuration {
public:
    Configuration();
    ~Configuration() = default;


    bool loadResources(const std::string& path) const;
    bool loadGameSettings(const std::string& path) const;
private:
    GameConfiguration m_gameConfiguration;
    ResourceConfiguration m_resourceConfiguration;
};


Configuration::Configuration() {}

bool Configuration::loadResources(const std::string& path) const {
    const std::string resourceSection = "Resources";

    std::unordered_map<ResourceID, std::string> resourceIDs = {
            {ResourceID::Audio, "audioDir"},
            {ResourceID::Font, "fontDir"},
            {ResourceID::Level, "levelDir"},
            {ResourceID::Texture, "textureDir"},
            {ResourceID::Shader, "shaderDir"},
    };


    INIReader reader(path);
    if(reader.ParseError() < 0) {
        LOG_ERROR("Can't read path % ", path.c_str());
        return false;
    }

    if (!reader.HasSection(resourceSection)){
        LOG_ERROR_E("No resources section")
        return false;
    }

    m_resourceConfiguration.audioDir = reader.GetString(resourceSection, resourceIDs[ResourceID::Audio], "");
    m_resourceConfiguration.fontDir = reader.GetString(resourceSection, resourceIDs[ResourceID::Font], "");
    m_resourceConfiguration.levelDir = reader.GetString(resourceSection, resourceIDs[ResourceID::Level], "");
    m_resourceConfiguration.textureDir = reader.GetString(resourceSection, resourceIDs[ResourceID::Texture], "");
    m_resourceConfiguration.shaderDir = reader.GetString(resourceSection, resourceIDs[ResourceID::Shader], "");

    std::cout << m_resourceConfiguration.audioDir << std::endl;
    std::cout << m_resourceConfiguration.fontDir << std::endl;
    std::cout << m_resourceConfiguration.levelDir << std::endl;
    std::cout << m_resourceConfiguration.textureDir << std::endl;
    std::cout << m_resourceConfiguration.shaderDir << std::endl;

    return true;
}



std::vector<std::string> split(const std::string& text, const std::string& sep){
    std::vector<std::string> res;
    std::size_t pos_start = 0U, pos_end, index = sep.length();

    while (( pos_end = text.find(sep, pos_start)) != std::string::npos ) {
        auto token = text.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + index;
        res.emplace_back(token);
    }

    res.emplace_back(text.substr(pos_start));

    return res;
}
const robot2D::vec2f badVector = robot2D::vec2f(-0.0002, -0.0002);
const std::string sep = ",";


robot2D::vec2f combineFromString(const std::string& text) {
    auto vec = split(text, sep);
    robot2D::vec2f res = badVector;
    if (vec.empty())
        return res;

    res.x = std::stof(vec[0]);
    res.y = std::stof(vec[1]);

    return res;
}

bool Configuration::loadGameSettings(const std::string& path) const {
    INIReader reader(path);
    if(reader.ParseError() < 0) {
        LOG_ERROR("Can't read path % ", path.c_str());
        return false;
    }

    const std::string gameSection = "Game";

    if (!reader.HasSection(gameSection)){
        LOG_ERROR_E("No game section")
        return false;
    }

    m_gameConfiguration.speed = reader.GetReal(gameSection, "speed", 0);
    m_gameConfiguration.ball_radius = reader.GetReal(gameSection,"ball_radius", 0);
    m_gameConfiguration.max_lives = reader.GetInteger(gameSection,"max_lives", 0);
    m_gameConfiguration.emitter_new_sz = reader.GetInteger(gameSection,"emitter_new_sz", 0);

    auto velocity_str = reader.GetString(gameSection, "ball_velocity", "");
    m_gameConfiguration.ball_velocity = combineFromString(velocity_str);

    auto paddle_str = reader.GetString(gameSection, "paddle_size", "");
    m_gameConfiguration.paddle_size = combineFromString(paddle_str);

    std::cout << m_gameConfiguration.ball_velocity.x << ':' << m_gameConfiguration.ball_velocity.y <<std::endl;

    return true;
}

int main() {
    Configuration configuration;
    if(!configuration.loadResources(resourceiniPath)){
        return -1;
    }
    if(!configuration.loadGameSettings("res/game.ini")){
        return -2;
    }

}