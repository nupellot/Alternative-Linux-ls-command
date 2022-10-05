{ pkgs }: {
	deps = [
		pkgs.execline.bin
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}