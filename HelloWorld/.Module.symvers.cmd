cmd_/home/debian/Projects/Kernel_Modules/HelloWorld/Module.symvers :=  sed 's/ko$$/o/'  /home/debian/Projects/Kernel_Modules/HelloWorld/modules.order | scripts/mod/modpost -m      -o /home/debian/Projects/Kernel_Modules/HelloWorld/Module.symvers -e -i Module.symvers -T - 
