with (import <nixpkgs> {});
mkShell {
  buildInputs = [
    gcc
    gnumake
    gdb
    cmake
    SDL2
    SDL2_ttf
    SDL2_image
    neofetch
  ];
}

