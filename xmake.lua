add_rules("mode.debug", "mode.release")

target("planefight_qt5")

    -- qt mingw在Windows平台上没有debug版本，因此只能够链接release版本的库
    add_rules("qt.widgetapp")
    add_files("src/*.cpp", "asset/planefight_qt5.qrc")
    add_files("src/GameScene.h", "src/Scene.h", "src/Window.h")

    if is_mode("debug") then
        add_defines("DEBUG")
    elseif is_mode("release") then
        add_defines("RELEASE")
    end

target_end()