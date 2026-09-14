add_executable(rns_app main.cpp)

# Линкуем
target_link_libraries(rns_app PRIVATE rns_core)