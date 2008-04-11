@echo off
echo [UTC 2008]
echo Converison Hex to Binary from elf
"C:\Keil\ARM\BIN30\fromelf.exe" --bin --output "C:\Keil\Projects\Test LCD\RVMDK\Keil\FLASH\project.bin" "C:\Keil\Projects\Test LCD\RVMDK\Keil\FLASH\project.axf"
echo on