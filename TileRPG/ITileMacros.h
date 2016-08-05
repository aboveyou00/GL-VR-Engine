#pragma once

#define SINGLETON_TILE_H(class_name)                    \
  private:                                              \
    class_name();                                       \
    ~class_name();                                      \
    static class_name *__instance;                      \
    static class_name *register_instance();             \
  public:                                               \
    inline static class_name &class_name::GetInstance() \
    {                                                   \
        return *__instance;                             \
    }

#define SINGLETON_TILE_CPP(class_name)                        \
    class_name *class_name::register_instance()               \
    {                                                         \
        class_name *tile = new class_name();                  \
        TileManager::GetInstance().RegisterTile(tile);        \
        return tile;                                          \
    }                                                         \
    class_name *class_name::__instance = register_instance();
