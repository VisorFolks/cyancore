#include <stdint.h>
#include <status.h>
#include <syslog.h>
#include <arch.h>
#include <platform.h>

void platform_print_cpu_info()
{
	unsigned int core_id = arch_core_index(),
		     isa = arch_core_isa(),
		     arch_id = arch_core_archid(),
		     imp_id = arch_core_impid(),
		     vendor_id = arch_core_vendor();

	syslog(info, "CPU Info: ID = %u\n-------------------------------\nISA\t\t: 0x%x\nArch ID\t\t: 0x%x\nImp ID\t\t: 0x%x\nVendor ID\t: 0x%x\n\n", core_id, isa, arch_id, imp_id, vendor_id);
};
