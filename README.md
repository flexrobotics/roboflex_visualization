# roboflex.visualization

A thin wrapper of various display nodes over SDL2. For now just supplies
one node: RGBImageTV. It can display rgb tensors of the form (H,W,3) uint8.

## System requirements

* libsdl: SDL (Simple Directmedia Layer)

        # search for existing libsdl packages
        dpkg -l | grep sdl # -> shows nothing

        # install libsdl
        sudo apt-get install libsdl2-dev

        # search for existing libsdl packages again
        dpkg -l | grep sdl # -> shows:
        ii  libsdl2-2.0-0:amd64                        2.0.20+dfsg-2ubuntu1.22.04.1                                        amd64        Simple DirectMedia Layer
        ii  libsdl2-dev:amd64                          2.0.20+dfsg-2ubuntu1.22.04.1                                        amd64        Simple DirectMedia Layer development files

        THIS, for me on ubuntu22, puts headers in /usr/include/SDL2 and libs in /lib/x86_64-linux-gnu/libSDL2-2.0.so

        # to remove it:
        sudo apt-get -y purge libsdl2-dev

## Import

    import roboflex.visualization as rv

## Nodes

There are two: 

There is are three: **RGBImageTV**, **BlackAndWhiteTV**, and **DepthTV**


    # RGBImageTV will redraw rgb images at some
    # frequency (refresh rate). It will look into
    # all messages it receives - those that contain
    # the key "rgb", mapping to a (3,H,W) tensor
    # will be rendered. Messages get propagated.

    rgb_tv = rcw.RGBImageTV(

        # mandatory (refresh rate)
        frequency_hz: float,

        # optional; defaults are:
        width = 640,
        height = 480,
        image_key = "rgb",
        initial_pos = (-1, -1),
        mirror = False,
        debug = False,
        name = "RGBImageTV"
    )

    # must be started!
    rgb_tv.start()


    # BlackAndWhiteTV will redraw rgb images at some
    # frequency (refresh rate). It will look into
    # all messages it receives - those that contain
    # the key "ir1", mapping to a (H,W) tensor
    # will be rendered. Messages get propagated.

    black_and_white_tv = rcw.BlackAndWhiteTV(

        # mandatory (refresh rate)
        frequency_hz: float,

        # optional; defaults are:
        width = 640,
        height = 480,
        image_key = "ir1",
        initial_pos = (-1, -1),
        mirror = False,
        debug = False,
        name = "BlackAndWhiteTV"
    )

    # must be started!
    black_and_white_tv.start()


    # DepthTV will redraw depth images at some
    # frequency (refresh rate). It will look into
    # all messages it receives - those that contain
    # the key "depth", mapping to a (H,W) tensor
    # will be rendered. Messages get propagated.

    depth_tv = rcw.DepthTV(

        # mandatory (refresh rate)
        frequency_hz: float,

        # optional; defaults are:
        width = 640,
        height = 480,
        image_key = "depth",
        initial_pos = (-1, -1),
        mirror = False,
        debug = False,
        name = "RGBImageTV"
    )

    # must be started!
    depth_tv.start()

