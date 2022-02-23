with (import <nixpkgs> {});
mkShell {
  buildInputs = [
    gcc
    gnumake
    gdb
    cmake
    SDL2
  ];
}

