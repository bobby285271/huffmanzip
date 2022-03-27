{ pkgs ? import <nixpkgs> { }
}:

with pkgs;

stdenv.mkDerivation rec {
  name = "huffmanzip";

  src = ./.;

  nativeBuildInputs = [
    meson
    ninja
    pkg-config
  ];

  buildInputs = [
    gtkmm3
  ];
}