/**
 * Copyright 2022 hupeng.
 * SPDX-License-Identifier: MIT
 */
#ifndef XORG_ELF_SPEC_H_
#define XORG_ELF_SPEC_H_

#include <bits/stdint-uintn.h>
#include <cstdint>

namespace xorg {

typedef uint64_t Elf64_Addr;
typedef uint16_t Elf64_Half;
typedef uint64_t Elf64_Off;
typedef int32_t Elf64_Sword;
typedef int64_t Elf64_Sxword;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Xword;
typedef uint8_t Elf64_Byte;
typedef uint16_t Elf64_Section;

static const intptr_t EI_NIDENT = 16;

#pragma pack(push, 1)

enum class EIdent : uint32_t {
  EI_MAG0 = 0,   // 0x7f
  EI_MAG1,       // 'E'
  EI_MAG2,       // 'L'
  EI_MAG3,       // 'F'
  EI_CLASS,      /* File class byte index */
  EI_DATA,       /* Data encoding byte index */
  EI_VERSION,    /* File version byte index, Value must be EV_CURRENT */
  EI_OSABI,      /* OS ABI identification */
  EI_ABIVERSION, /* ABI version */
  EI_PAD,        /* Byte index of padding bytes */
};

enum class EIClass : uint32_t {
  ELFCLASSNONE = 0, /* Invalid class */
  ELFCLASS32,       /* 32-bit objects */
  ELFCLASS64,       /* 64-bit objects */
};

enum class EIdata : uint32_t {
  ELFDATANONE = 0, /* Invalid data encoding */
  ELFDATA2LSB,     /* 2's complement, little endian */
  ELFDATA2MSB,     /* 2's complement, big endian */
};

enum class EVersion : uint32_t {
  EV_NONE = 0, /* Invalid ELF version */
  EV_CURRENT,  /* Current version */
};

enum class EIOsabi : uint32_t {
  ELFOSABI_NONE = 0,             /* UNIX System V ABI */
  ELFOSABI_SYSV = 0,             /* Alias.  */
  ELFOSABI_GNU = 3,              /* Object uses GNU ELF extensions.  */
  ELFOSABI_LINUX = ELFOSABI_GNU, /* Compatibility alias.  */
  ELFOSABI_SOLARIS = 6,          /* Sun Solaris.  */
  ELFOSABI_ARM_AEABI = 64,       /* ARM EABI */
  ELFOSABI_ARM = 97,             /* ARM */
  ELFOSABI_STANDALONE = 255,     /* Standalone (embedded) application */
};

enum class EType : uint32_t {
  ET_NONE = 0,        /* No file type */
  ET_REL,             /* Relocatable file */
  ET_EXEC,            /* Executable file */
  ET_DYN,             /* Shared object file */
  ET_CORE,            /* Core file */
  ET_LOOS = 0xfe00,   /* OS-specific range start */
  ET_HIOS = 0xfeff,   /* OS-specific range end */
  ET_LOPROC = 0xff00, /* Processor-specific range start */
  ET_HIPROC = 0xffff, /* Processor-specific range end */
};

enum class EMachine : uint32_t {
  EM_NONE = 0,        /* No machine */
  EM_386 = 3,         /* Intel 80386 */
  EM_MIPS = 8,        /* MIPS R3000 big-endian */
  EM_ARM = 40,        /* ARM */
  EM_IA_64 = 50,      /* Intel Merced */
  EM_X86_64 = 62,     /* AMD x86-64 architecture */
  EM_AARCH64 = 183,   /* ARM AARCH64 */
  EM_RISCV = 243,     /* RISC-V */
  EM_BPF = 247,       /* Linux BPF -- in-kernel virtual machine */
  EM_CSKY = 252,      /* C-SKY */
  EM_LOONGARCH = 258, /* LoongArch */
};

struct Elf64_Ehdr {
  unsigned char e_ident[EI_NIDENT]; /* Magic number and other info */
  Elf64_Half e_type;                /* Object file type */
  Elf64_Half e_machine;             /* Architecture */
  Elf64_Word e_version;             /* Object file version */
  Elf64_Addr e_entry;               /* Entry point virtual address */
  Elf64_Off e_phoff;                /* Program header table file offset */
  Elf64_Off e_shoff;                /* Section header table file offset */
  Elf64_Word e_flags;               /* Processor-specific flags */
  Elf64_Half e_ehsize;              /* ELF header size in bytes */
  Elf64_Half e_phentsize;           /* Program header table entry size */
  Elf64_Half e_phnum;               /* Program header table entry count */
  Elf64_Half e_shentsize;           /* Section header table entry size */
  Elf64_Half e_shnum;               /* Section header table entry count */
  Elf64_Half e_shstrndx;            /* Section header string table index */
};

enum class SHType : uint32_t {
  SHT_NULL = 0,                    /* Section header table entry unused */
  SHT_PROGBITS,                    /* Program data */
  SHT_SYMTAB,                      /* Symbol table */
  SHT_STRTAB,                      /* String table */
  SHT_RELA,                        /* Relocation entries with addends */
  SHT_HASH,                        /* Symbol hash table */
  SHT_DYNAMIC,                     /* Dynamic linking information */
  SHT_NOTE,                        /* Notes */
  SHT_NOBITS,                      /* Program space with no data (bss) */
  SHT_REL,                         /* Relocation entries, no addends */
  SHT_SHLIB,                       /* Reserved */
  SHT_DYNSYM,                      /* Dynamic linker symbol table */
  SHT_INIT_ARRAY = 14,             /* Array of constructors */
  SHT_FINI_ARRAY,                  /* Array of destructors */
  SHT_PREINIT_ARRAY,               /* Array of pre-constructors */
  SHT_GROUP,                       /* Section group */
  SHT_SYMTAB_SHNDX,                /* Extended section indeces */
  SHT_GNU_ATTRIBUTES = 0x6ffffff5, /* Object attributes.  */
  SHT_GNU_HASH,                    /* GNU-style hash table.  */
  SHT_GNU_LIBLIST,                 /* Prelink library list */
  SHT_CHECKSUM,                    /* Checksum for DSO content.  */
  SHT_GNU_VERDEF = 0x6ffffffd,     /* Version definition section.  */
  SHT_GNU_VERNEED,                 /* Version needs section.  */
  SHT_GNU_VERSYM,                  /* Version symbol table.  */
};

enum class SHFlags : uint32_t {
  SHF_WRITE = (1 << 0),      /* Writable */
  SHF_ALLOC = (1 << 1),      /* Occupies memory during execution */
  SHF_EXECINSTR = (1 << 2),  /* Executable */
  SHF_MERGE = (1 << 4),      /* Might be merged */
  SHF_STRINGS = (1 << 5),    /* Contains nul-terminated strings */
  SHF_INFO_LINK = (1 << 6),  /* `sh_info' contains SHT index */
  SHF_LINK_ORDER = (1 << 7), /* Preserve order after combining */
  SHF_OS_NONCONFORMING =
      (1 << 8),               /* Non-standard OS specific handling required */
  SHF_GROUP = (1 << 9),       /* Section is member of a group.  */
  SHF_TLS = (1 << 10),        /* Section hold thread-local data.  */
  SHF_COMPRESSED = (1 << 11), /* Section with compressed data. */
  SHF_ORDERED = (1 << 30),    /* Special ordering requirement (Solaris).  */
  SHF_EXCLUDE = (1U << 31),   /* Section is excluded unless referenced or
                                 allocated (Solaris).*/
};

struct Elf64_Shdr {
  Elf64_Word sh_name;       /* Section name (string tbl index) */
  Elf64_Word sh_type;       /* Section type */
  Elf64_Xword sh_flags;     /* Section flags */
  Elf64_Addr sh_addr;       /* Section virtual addr at execution */
  Elf64_Off sh_offset;      /* Section file offset */
  Elf64_Xword sh_size;      /* Section size in bytes */
  Elf64_Word sh_link;       /* Link to another section */
  Elf64_Word sh_info;       /* Additional section information */
  Elf64_Xword sh_addralign; /* Section alignment */
  Elf64_Xword sh_entsize;   /* Entry size if section holds table */
};

enum class PHType : uint32_t {
  PT_NULL = 0,                  /* Program header table entry unused */
  PT_LOAD,                      /* Loadable program segment */
  PT_DYNAMIC,                   /* Dynamic linking information */
  PT_INTERP,                    /* Program interpreter */
  PT_NOTE,                      /* Auxiliary information */
  PT_SHLIB,                     /* Reserved */
  PT_PHDR,                      /* Entry for header table itself */
  PT_TLS,                       /* Thread-local storage segment */
  PT_GNU_EH_FRAME = 0x6474e550, /* GCC .eh_frame_hdr segment */
  PT_GNU_STACK,                 /* Indicates stack executability */
  PT_GNU_RELRO,                 /* Read-only after relocation */
};

enum class PHFlag : uint32_t {
  PF_X = (1 << 0), /* Segment is executable */
  PF_W = (1 << 1), /* Segment is writable */
  PF_R = (1 << 2), /* Segment is readable */
};

struct Elf64_Phdr {
  Elf64_Word p_type;    /* Segment type */
  Elf64_Word p_flags;   /* Segment flags */
  Elf64_Off p_offset;   /* Segment file offset */
  Elf64_Addr p_vaddr;   /* Segment virtual address */
  Elf64_Addr p_paddr;   /* Segment physical address */
  Elf64_Xword p_filesz; /* Segment size in file */
  Elf64_Xword p_memsz;  /* Segment size in memory */
  Elf64_Xword p_align;  /* Segment alignment */
};

enum class STBind : uint32_t {
  STB_LOCAL = 0,       /* Local symbol */
  STB_GLOBAL,          /* Global symbol */
  STB_WEAK,            /* Weak symbol */
  STB_NUM,             /* Number of defined types.  */
  STB_LOOS = 10,       /* Start of OS-specific */
  STB_GNU_UNIQUE = 10, /* Unique symbol.  */
  STB_HIOS = 12,       /* End of OS-specific */
  STB_LOPROC = 13,     /* Start of processor-specific */
  STB_HIPROC = 15,     /* End of processor-specific */
};

enum class STType : uint32_t {
  STT_NOTYPE = 0,     /* Symbol type is unspecified */
  STT_OBJECT,         /* Symbol is a data object */
  STT_FUNC,           /* Symbol is a code object */
  STT_SECTION,        /* Symbol associated with a section */
  STT_FILE,           /* Symbol's name is file name */
  STT_COMMON,         /* Symbol is a common data object */
  STT_TLS,            /* Symbol is thread-local data object*/
  STT_NUM,            /* Number of defined types.  */
  STT_LOOS = 10,      /* Start of OS-specific */
  STT_GNU_IFUNC = 10, /* Symbol is indirect code object */
  STT_HIOS = 12,      /* End of OS-specific */
  STT_LOPROC = 13,    /* Start of processor-specific */
  STT_HIPROC = 15,    /* End of processor-specific */
};

enum class STVisable : uint32_t {
  STV_DEFAULT = 0, /* Default symbol visibility rules */
  STV_INTERNAL,    /* Processor specific hidden class */
  STV_HIDDEN,      /* Sym unavailable in other modules */
  STV_PROTECTED,   /* Not preemptible, not exported */
};

enum class SHNdx : uint32_t {
  SHN_UNDEF = 0,          /* Undefined section */
  SHN_LORESERVE = 0xff00, /* Start of reserved indices */
  SHN_LOPROC = 0xff00,    /* Start of processor-specific */
  SHN_HIPROC = 0xff1f,    /* End of processor-specific */
  SHN_LOOS = 0xff20,      /* Start of OS-specific */
  SHN_HIOS = 0xff3f,      /* End of OS-specific */
  SHN_ABS = 0xfff1,       /* Associated symbol is absolute */
  SHN_COMMON = 0xfff2,    /* Associated symbol is common */
  SHN_XINDEX = 0xffff,    /* Index is in extra table.  */
  SHN_HIRESERVE = 0xffff, /* End of reserved indices */
};

struct Elf64_Sym {
  Elf64_Word st_name;     /* Symbol name (string tbl index) */
  unsigned char st_info;  /* Symbol type and binding */
  unsigned char st_other; /* Symbol visibility */
  Elf64_Section st_shndx; /* Section index */
  Elf64_Addr st_value;    /* Symbol value */
  Elf64_Xword st_size;    /* Symbol size */
};

#pragma pack(pop)

}  // namespace xorg

#endif  // XORG_ELF_SPEC_H_
