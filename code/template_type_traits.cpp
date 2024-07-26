#include <iostream>
#include <string>

enum DeviceInfoTag
{
    Id,
    Name,
    Type,
    Size,
    MaxSpeed,
};

enum EnvInfoTag
{
    Density,
    Temperature,
    Pressure,
};

struct Device
{
    std::string data = "I am a device";
};

struct Environment
{
    std::string data = "I am an environment";
};

std::string get_info(Device* device, DeviceInfoTag tag)
{
    switch (tag)
    {
    case Id:
        return "Device ID";
    case Name:
        return "Device Name";
    case Type:
        return "Device Type";
    case Size:
        return "Device Size";
    case MaxSpeed:
        return "Device Max Speed";
    default:
        return "Unknown Device Info";
    }
}

double get_info(Environment* environment, EnvInfoTag tag)
{
    switch (tag)
    {
    case Density:
        return 1.0;
    case Temperature:
        return 2.0;
    case Pressure:
        return 3.0;
    default:
        return -1.0;
    }
}

// clang-format off

// Empty primary template to generate an error by default
template <typename T, int Name> struct param_traits {};

// One of many specialisations to match specific Tag::Value to return type.
// Example: `EnvInfoTag::Pressure` should return `double`.
template <> struct param_traits<EnvInfoTag, Pressure>
{
    enum { value = Pressure };
    using type = double;
};

template <> struct param_traits<EnvInfoTag, MaxSpeed>
{
    enum { value = MaxSpeed };
    using type = double;
};

template <> struct param_traits<EnvInfoTag, Name>
{
    enum { value = Name };
    using type = std::string;
};

// clang-format on

class DeviceWrapper
{
    Device* dev_;
public:
    DeviceWrapper(Device* dev) : dev_(dev) {}

    template <DeviceInfoTag name>
    typename param_traits<DeviceInfoTag, name>::type getInfo()
    {
        get_info(dev_, name);
    }
};

class EnviromentWrapper
{
    Environment* env_;
public:
    EnviromentWrapper(Environment* env) : env_(env) {}

    template <EnvInfoTag name>
    typename param_traits<EnvInfoTag, name>::type getInfo()
    {
        get_info(env_, name);
    }
};

int main()
{
    Device dev;
    Environment env;

    DeviceWrapper devWrapper(&dev);
    EnviromentWrapper envWrapper(&env);

    // TODO - doesn't compile. See https://youtu.be/UrL5gdW2JOM?t=1281
    devWrapper.getInfo<Pressure>();
}