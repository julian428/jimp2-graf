{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = [ pkgs.curl.dev pkgs.cjson pkgs.gcc ];
}
