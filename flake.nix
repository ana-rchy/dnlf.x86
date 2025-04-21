{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.11";
  };
    
  outputs = { nixpkgs, ... }: rec {
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages."${system}";
    
    devShells."${system}".default = pkgs.mkShell {
      packages = with pkgs; [
        gcc
        raylib
      ];
      
      shellHook = ''
        exec zsh
      '';
    };
  };
}
