{
  description = "USACO programming";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }: 
    let
      supportedSystems = [ "x86_64-linux" "x86_64-darwin" "aarch64-linux" "aarch64-darwin" ];
      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;
      nixpkgsFor = forAllSystems (system: nixpkgs.legacyPackages.${system});
    in
    {
    packages = forAllSystems (system: 
      let
        pkgs = nixpkgsFor.${system};
	packages.default = pkgs.stdenv.mkDerivation {
	  pname = "USACO";
	  version = "0.1";
	  nativeBuildInputs = [
	  pkgs.cmake
	  pkgs.gcc
	  pkgs.git
	  pkgs.codespell
	  pkgs.cppcheck
	  pkgs.doxygen
	  pkgs.vcpkg
          pkgs.clang-tools
	  ];
	  src = ./.;
	  buildPhase = ''
	    echo "Building cmake..."
	    cmake ..
	    echo "Done building cmake"
	    echo "Building program..."
	    make
	    echo "Done building program"
	  '';
	  installPhase = ''
	    make install
	  '';
	};
      in
      nixpkgs.lib.filterAttrs (_: nixpkgs.lib.meta.availableOn pkgs.stdenv.hostPlatform) packages
    );
  };
}
