.PHONY: all
all: Hyperion.iso

.PHONY: all-hdd
all-hdd: Hyperion.hdd

.PHONY: run
run: Hyperion.iso
	"F:\Quality Software\OperatingSystemDevTools\vms\qemu-system-x86_64.exe" -M q35 -m 512M -smp 8 -serial stdio -cdrom Hyperion.iso -boot d

.PHONY: run-uefi
run-uefi: ovmf-x64 Hyperion.iso
	"F:\Quality Software\OperatingSystemDevTools\vms\qemu-system-x86_64.exe" -M q35 -m 8G -smp 8 -bios ovmf-x64\OVMF.fd -cdrom Hyperion.iso -boot d

.PHONY: run-hdd
run-hdd: Hyperion.hdd
	"F:\Quality Software\OperatingSystemDevTools\vms\qemu-system-x86_64.exe" -M q35 -m 8G -smp 8 -hda Hyperion.hdd

.PHONY: run-hdd-uefi
run-hdd-uefi: ovmf-x64 Hyperion.hdd
	"F:\Quality Software\OperatingSystemDevTools\vms\qemu-system-x86_64.exe" -M q35 -m 8G -smp 8 -bios ovmf-x64\OVMF.fd -hda Hyperion.hdd

ovmf-x64:
	mkdir -p ovmf-x64
	cd ovmf-x64 && curl -o OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip && 7z x OVMF-X64.zip

limine:
	@echo [== DOWNLOADING LIMINE BOOTLOADER FROM GITHUB ==]
	git clone https://github.com/limine-bootloader/limine.git --branch=v3.0-branch-binary --depth=1
	
	@echo [== COMPILING LIMINE ==]
	make -C limine

	@echo [== LIMINE COMPILATION FINISHED ==]

.PHONY: kernel
kernel:
	@echo [== COMPILING KERNEL ==]
	$(MAKE) -C kernel

#rmdir /s iso_root
Hyperion.iso: limine kernel
	@echo [== REMOVING DIRECTORIES ==]
	rm -rf iso_root

	@echo "\n"
	@echo [== MAKING DIRECTORIES ==]
	mkdir -p iso_root

	@echo "\n"
	@echo [== COPYING FILES ==]
	cp kernel/kernel.elf iso_root
	cp modules/ramdisk.tar iso_root
	cp modules/background.bmp iso_root
	cp limine.cfg iso_root
	cp limine/limine.sys iso_root
	cp limine/limine-cd.bin iso_root
	cp limine/limine-cd-efi.bin iso_root

	@echo "\n"
	@echo [== CREATING ISO IMAGE ==]
	xorriso -as mkisofs -b limine-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot limine-cd-efi.bin -efi-boot-part --efi-boot-image --protective-msdos-label	iso_root -o Hyperion.iso
	
	@echo "\n"
	@echo [== DEPLOYING LIMINE BOOTLOADER ==]
	limine/limine-deploy.exe Hyperion.iso

	@echo "\n"
	@echo [== BUILD COMPLETED ==]

.PHONY: clean
clean:
	rm -rf iso_root
	rm Hyperion.iso
	$(MAKE) -C kernel clean

.PHONY: distclean
distclean: clean
	rm -rf limine ovmf-x64
	$(MAKE) -C kernel distclean
