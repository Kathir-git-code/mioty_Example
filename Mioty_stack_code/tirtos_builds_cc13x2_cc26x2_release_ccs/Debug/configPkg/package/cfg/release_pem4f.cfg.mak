# invoke SourceDir generated makefile for release.pem4f
release.pem4f: .libraries,release.pem4f
.libraries,release.pem4f: package/cfg/release_pem4f.xdl
	$(MAKE) -f D:\Development\workfolder\Mioty_statck_code\tirtos_builds_cc13x2_cc26x2_release_ccs/src/makefile.libs

clean::
	$(MAKE) -f D:\Development\workfolder\Mioty_statck_code\tirtos_builds_cc13x2_cc26x2_release_ccs/src/makefile.libs clean

