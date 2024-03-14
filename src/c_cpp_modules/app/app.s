
app.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <app_exit_error>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10:	48 8b 05 00 00 00 00 	mov    0x0(%rip),%rax        # 17 <app_exit_error+0x17>
  17:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
  1b:	48 8d 0d 00 00 00 00 	lea    0x0(%rip),%rcx        # 22 <app_exit_error+0x22>
  22:	48 89 ce             	mov    %rcx,%rsi
  25:	48 89 c7             	mov    %rax,%rdi
  28:	b8 00 00 00 00       	mov    $0x0,%eax
  2d:	e8 00 00 00 00       	call   32 <app_exit_error+0x32>
  32:	bf ff ff ff ff       	mov    $0xffffffff,%edi
  37:	e8 00 00 00 00       	call   3c <tnt_getcwd>

000000000000003c <tnt_getcwd>:
  3c:	f3 0f 1e fa          	endbr64 
  40:	55                   	push   %rbp
  41:	48 89 e5             	mov    %rsp,%rbp
  44:	48 83 ec 20          	sub    $0x20,%rsp
  48:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
  4f:	00 
  50:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  57:	00 
  58:	48 c7 45 f0 00 01 00 	movq   $0x100,-0x10(%rbp)
  5f:	00 
  60:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  64:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  68:	48 89 d6             	mov    %rdx,%rsi
  6b:	48 89 c7             	mov    %rax,%rdi
  6e:	e8 00 00 00 00       	call   73 <tnt_getcwd+0x37>
  73:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  77:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  7c:	75 0f                	jne    8d <tnt_getcwd+0x51>
  7e:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 85 <tnt_getcwd+0x49>
  85:	48 89 c7             	mov    %rax,%rdi
  88:	e8 00 00 00 00       	call   8d <tnt_getcwd+0x51>
  8d:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  91:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  95:	48 89 d6             	mov    %rdx,%rsi
  98:	48 89 c7             	mov    %rax,%rdi
  9b:	e8 00 00 00 00       	call   a0 <tnt_getcwd+0x64>
  a0:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  a4:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  a9:	75 34                	jne    df <tnt_getcwd+0xa3>
  ab:	e8 00 00 00 00       	call   b0 <tnt_getcwd+0x74>
  b0:	8b 00                	mov    (%rax),%eax
  b2:	83 f8 22             	cmp    $0x22,%eax
  b5:	74 28                	je     df <tnt_getcwd+0xa3>
  b7:	e8 00 00 00 00       	call   bc <tnt_getcwd+0x80>
  bc:	8b 00                	mov    (%rax),%eax
  be:	89 c7                	mov    %eax,%edi
  c0:	e8 00 00 00 00       	call   c5 <tnt_getcwd+0x89>
  c5:	48 89 c6             	mov    %rax,%rsi
  c8:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # cf <tnt_getcwd+0x93>
  cf:	48 89 c7             	mov    %rax,%rdi
  d2:	e8 00 00 00 00       	call   d7 <tnt_getcwd+0x9b>
  d7:	48 89 c7             	mov    %rax,%rdi
  da:	e8 00 00 00 00       	call   df <tnt_getcwd+0xa3>
  df:	48 d1 65 f0          	shlq   -0x10(%rbp)
  e3:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  e8:	0f 84 72 ff ff ff    	je     60 <tnt_getcwd+0x24>
  ee:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  f2:	c9                   	leave  
  f3:	c3                   	ret    

00000000000000f4 <app_select_dst>:
  f4:	f3 0f 1e fa          	endbr64 
  f8:	55                   	push   %rbp
  f9:	48 89 e5             	mov    %rsp,%rbp
  fc:	48 83 ec 10          	sub    $0x10,%rsp
 100:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 104:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 10b <app_select_dst+0x17>
 10b:	48 89 c7             	mov    %rax,%rdi
 10e:	e8 00 00 00 00       	call   113 <app_select_dst+0x1f>
 113:	90                   	nop
 114:	c9                   	leave  
 115:	c3                   	ret    

0000000000000116 <app_dep_add>:
 116:	f3 0f 1e fa          	endbr64 
 11a:	55                   	push   %rbp
 11b:	48 89 e5             	mov    %rsp,%rbp
 11e:	48 83 ec 10          	sub    $0x10,%rsp
 122:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 126:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 12d <app_dep_add+0x17>
 12d:	48 89 c7             	mov    %rax,%rdi
 130:	e8 00 00 00 00       	call   135 <app_dep_add+0x1f>
 135:	90                   	nop
 136:	c9                   	leave  
 137:	c3                   	ret    

0000000000000138 <app_dep_rm>:
 138:	f3 0f 1e fa          	endbr64 
 13c:	55                   	push   %rbp
 13d:	48 89 e5             	mov    %rsp,%rbp
 140:	48 83 ec 10          	sub    $0x10,%rsp
 144:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 148:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 14f <app_dep_rm+0x17>
 14f:	48 89 c7             	mov    %rax,%rdi
 152:	e8 00 00 00 00       	call   157 <app_dep_rm+0x1f>
 157:	90                   	nop
 158:	c9                   	leave  
 159:	c3                   	ret    

000000000000015a <app_rel_add>:
 15a:	f3 0f 1e fa          	endbr64 
 15e:	55                   	push   %rbp
 15f:	48 89 e5             	mov    %rsp,%rbp
 162:	48 83 ec 10          	sub    $0x10,%rsp
 166:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 16a:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 171 <app_rel_add+0x17>
 171:	48 89 c7             	mov    %rax,%rdi
 174:	e8 00 00 00 00       	call   179 <app_rel_add+0x1f>
 179:	90                   	nop
 17a:	c9                   	leave  
 17b:	c3                   	ret    

000000000000017c <app_rel_rm>:
 17c:	f3 0f 1e fa          	endbr64 
 180:	55                   	push   %rbp
 181:	48 89 e5             	mov    %rsp,%rbp
 184:	48 83 ec 10          	sub    $0x10,%rsp
 188:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 18c:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 193 <app_rel_rm+0x17>
 193:	48 89 c7             	mov    %rax,%rdi
 196:	e8 00 00 00 00       	call   19b <app_rel_rm+0x1f>
 19b:	90                   	nop
 19c:	c9                   	leave  
 19d:	c3                   	ret    

000000000000019e <app_set_build_script>:
 19e:	f3 0f 1e fa          	endbr64 
 1a2:	55                   	push   %rbp
 1a3:	48 89 e5             	mov    %rsp,%rbp
 1a6:	48 83 ec 10          	sub    $0x10,%rsp
 1aa:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 1ae:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 1b5 <app_set_build_script+0x17>
 1b5:	48 89 c7             	mov    %rax,%rdi
 1b8:	e8 00 00 00 00       	call   1bd <app_set_build_script+0x1f>
 1bd:	90                   	nop
 1be:	c9                   	leave  
 1bf:	c3                   	ret    

00000000000001c0 <app_set_onchange_script>:
 1c0:	f3 0f 1e fa          	endbr64 
 1c4:	55                   	push   %rbp
 1c5:	48 89 e5             	mov    %rsp,%rbp
 1c8:	48 83 ec 10          	sub    $0x10,%rsp
 1cc:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 1d0:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 1d7 <app_set_onchange_script+0x17>
 1d7:	48 89 c7             	mov    %rax,%rdi
 1da:	e8 00 00 00 00       	call   1df <app_set_onchange_script+0x1f>
 1df:	90                   	nop
 1e0:	c9                   	leave  
 1e1:	c3                   	ret    

00000000000001e2 <app_chdir>:
 1e2:	f3 0f 1e fa          	endbr64 
 1e6:	55                   	push   %rbp
 1e7:	48 89 e5             	mov    %rsp,%rbp
 1ea:	48 83 ec 10          	sub    $0x10,%rsp
 1ee:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 1f2:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 1f9 <app_chdir+0x17>
 1f9:	48 89 c7             	mov    %rax,%rdi
 1fc:	e8 00 00 00 00       	call   201 <app_chdir+0x1f>
 201:	90                   	nop
 202:	c9                   	leave  
 203:	c3                   	ret    

0000000000000204 <app_get_tar>:
 204:	f3 0f 1e fa          	endbr64 
 208:	55                   	push   %rbp
 209:	48 89 e5             	mov    %rsp,%rbp
 20c:	48 83 ec 10          	sub    $0x10,%rsp
 210:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 214:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 21b <app_get_tar+0x17>
 21b:	48 89 c7             	mov    %rax,%rdi
 21e:	e8 00 00 00 00       	call   223 <app_get_tar+0x1f>
 223:	90                   	nop
 224:	c9                   	leave  
 225:	c3                   	ret    

0000000000000226 <app_get_dep>:
 226:	f3 0f 1e fa          	endbr64 
 22a:	55                   	push   %rbp
 22b:	48 89 e5             	mov    %rsp,%rbp
 22e:	48 83 ec 10          	sub    $0x10,%rsp
 232:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 236:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 23d <app_get_dep+0x17>
 23d:	48 89 c7             	mov    %rax,%rdi
 240:	e8 00 00 00 00       	call   245 <app_get_dep+0x1f>
 245:	90                   	nop
 246:	c9                   	leave  
 247:	c3                   	ret    

0000000000000248 <app_get_rel>:
 248:	f3 0f 1e fa          	endbr64 
 24c:	55                   	push   %rbp
 24d:	48 89 e5             	mov    %rsp,%rbp
 250:	48 83 ec 10          	sub    $0x10,%rsp
 254:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 258:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 25f <app_get_rel+0x17>
 25f:	48 89 c7             	mov    %rax,%rdi
 262:	e8 00 00 00 00       	call   267 <app_get_rel+0x1f>
 267:	90                   	nop
 268:	c9                   	leave  
 269:	c3                   	ret    

000000000000026a <app_get_build_script>:
 26a:	f3 0f 1e fa          	endbr64 
 26e:	55                   	push   %rbp
 26f:	48 89 e5             	mov    %rsp,%rbp
 272:	48 83 ec 10          	sub    $0x10,%rsp
 276:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 27a:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 281 <app_get_build_script+0x17>
 281:	48 89 c7             	mov    %rax,%rdi
 284:	e8 00 00 00 00       	call   289 <app_get_build_script+0x1f>
 289:	90                   	nop
 28a:	c9                   	leave  
 28b:	c3                   	ret    

000000000000028c <app_get_onchange_script>:
 28c:	f3 0f 1e fa          	endbr64 
 290:	55                   	push   %rbp
 291:	48 89 e5             	mov    %rsp,%rbp
 294:	48 83 ec 10          	sub    $0x10,%rsp
 298:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 29c:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 2a3 <app_get_onchange_script+0x17>
 2a3:	48 89 c7             	mov    %rax,%rdi
 2a6:	e8 00 00 00 00       	call   2ab <app_get_onchange_script+0x1f>
 2ab:	90                   	nop
 2ac:	c9                   	leave  
 2ad:	c3                   	ret    

Disassembly of section .rodata:

0000000000000000 <.rodata>:
   0:	45 52                	rex.RB push %r10
   2:	52                   	push   %rdx
   3:	4f 52                	rex.WRXB push %r10
   5:	3a 20                	cmp    (%rax),%ah
   7:	25 73 0a 00 00       	and    $0xa73,%eax
   c:	00 00                	add    %al,(%rax)
   e:	00 00                	add    %al,(%rax)
  10:	74 6e                	je     80 <.rodata+0x80>
  12:	74 5f                	je     73 <.rodata+0x73>
  14:	67 65 74 63          	addr32 gs je 7b <.rodata+0x7b>
  18:	77 64                	ja     7e <.rodata+0x7e>
  1a:	2c 20                	sub    $0x20,%al
  1c:	63 77 64             	movsxd 0x64(%rdi),%esi
  1f:	3a 20                	cmp    (%rax),%ah
  21:	43 61                	rex.XB (bad) 
  23:	6e                   	outsb  %ds:(%rsi),(%dx)
  24:	6e                   	outsb  %ds:(%rsi),(%dx)
  25:	6f                   	outsl  %ds:(%rsi),(%dx)
  26:	74 20                	je     48 <.rodata+0x48>
  28:	61                   	(bad)  
  29:	6c                   	insb   (%dx),%es:(%rdi)
  2a:	6c                   	insb   (%dx),%es:(%rdi)
  2b:	6f                   	outsl  %ds:(%rsi),(%dx)
  2c:	63 61 74             	movsxd 0x74(%rcx),%esp
  2f:	65 20 65 6e          	and    %ah,%gs:0x6e(%rbp)
  33:	6f                   	outsl  %ds:(%rsi),(%dx)
  34:	75 67                	jne    9d <.rodata+0x9d>
  36:	68 20 6d 65 6d       	push   $0x6d656d20
  3b:	6f                   	outsl  %ds:(%rsi),(%dx)
  3c:	72 79                	jb     b7 <.rodata+0xb7>
  3e:	2e 00 74 6e 74       	cs add %dh,0x74(%rsi,%rbp,2)
  43:	5f                   	pop    %rdi
  44:	67 65 74 63          	addr32 gs je ab <.rodata+0xab>
  48:	77 64                	ja     ae <.rodata+0xae>
  4a:	2c 20                	sub    $0x20,%al
  4c:	67 65 74 63          	addr32 gs je b3 <.rodata+0xb3>
  50:	77 64                	ja     b6 <.rodata+0xb6>
  52:	00 61 70             	add    %ah,0x70(%rcx)
  55:	70 5f                	jo     b6 <.rodata+0xb6>
  57:	73 65                	jae    be <.rodata+0xbe>
  59:	6c                   	insb   (%dx),%es:(%rdi)
  5a:	65 63 74 5f 64       	movsxd %gs:0x64(%rdi,%rbx,2),%esi
  5f:	73 74                	jae    d5 <.rodata+0xd5>
  61:	00 61 70             	add    %ah,0x70(%rcx)
  64:	70 5f                	jo     c5 <.rodata+0xc5>
  66:	64 65 70 5f          	fs gs jo c9 <.rodata+0xc9>
  6a:	61                   	(bad)  
  6b:	64 64 00 61 70       	fs add %ah,%fs:0x70(%rcx)
  70:	70 5f                	jo     d1 <.rodata+0xd1>
  72:	64 65 70 5f          	fs gs jo d5 <.rodata+0xd5>
  76:	72 6d                	jb     e5 <.rodata+0xe5>
  78:	00 61 70             	add    %ah,0x70(%rcx)
  7b:	70 5f                	jo     dc <.rodata+0xdc>
  7d:	72 65                	jb     e4 <.rodata+0xe4>
  7f:	6c                   	insb   (%dx),%es:(%rdi)
  80:	5f                   	pop    %rdi
  81:	61                   	(bad)  
  82:	64 64 00 61 70       	fs add %ah,%fs:0x70(%rcx)
  87:	70 5f                	jo     e8 <.rodata+0xe8>
  89:	72 65                	jb     f0 <.rodata+0xf0>
  8b:	6c                   	insb   (%dx),%es:(%rdi)
  8c:	5f                   	pop    %rdi
  8d:	72 6d                	jb     fc <.rodata+0xfc>
  8f:	00 61 70             	add    %ah,0x70(%rcx)
  92:	70 5f                	jo     f3 <.rodata+0xf3>
  94:	73 65                	jae    fb <.rodata+0xfb>
  96:	74 5f                	je     f7 <.rodata+0xf7>
  98:	62 75                	(bad)  
  9a:	69 6c 64 5f 73 63 72 	imul   $0x69726373,0x5f(%rsp,%riz,2),%ebp
  a1:	69 
  a2:	70 74                	jo     118 <app_dep_add+0x2>
  a4:	00 61 70             	add    %ah,0x70(%rcx)
  a7:	70 5f                	jo     108 <.rodata+0x108>
  a9:	73 65                	jae    110 <.rodata+0x110>
  ab:	74 5f                	je     10c <.rodata+0x10c>
  ad:	6f                   	outsl  %ds:(%rsi),(%dx)
  ae:	6e                   	outsb  %ds:(%rsi),(%dx)
  af:	63 68 61             	movsxd 0x61(%rax),%ebp
  b2:	6e                   	outsb  %ds:(%rsi),(%dx)
  b3:	67 65 5f             	addr32 gs pop %rdi
  b6:	73 63                	jae    11b <app_dep_add+0x5>
  b8:	72 69                	jb     123 <app_dep_add+0xd>
  ba:	70 74                	jo     130 <app_dep_add+0x1a>
  bc:	00 61 70             	add    %ah,0x70(%rcx)
  bf:	70 5f                	jo     120 <app_dep_add+0xa>
  c1:	63 68 64             	movsxd 0x64(%rax),%ebp
  c4:	69 72 00 61 70 70 5f 	imul   $0x5f707061,0x0(%rdx),%esi
  cb:	67 65 74 5f          	addr32 gs je 12e <app_dep_add+0x18>
  cf:	74 61                	je     132 <app_dep_add+0x1c>
  d1:	72 00                	jb     d3 <.rodata+0xd3>
  d3:	61                   	(bad)  
  d4:	70 70                	jo     146 <app_dep_rm+0xe>
  d6:	5f                   	pop    %rdi
  d7:	67 65 74 5f          	addr32 gs je 13a <app_dep_rm+0x2>
  db:	64 65 70 00          	fs gs jo df <.rodata+0xdf>
  df:	61                   	(bad)  
  e0:	70 70                	jo     152 <app_dep_rm+0x1a>
  e2:	5f                   	pop    %rdi
  e3:	67 65 74 5f          	addr32 gs je 146 <app_dep_rm+0xe>
  e7:	72 65                	jb     14e <app_dep_rm+0x16>
  e9:	6c                   	insb   (%dx),%es:(%rdi)
  ea:	00 61 70             	add    %ah,0x70(%rcx)
  ed:	70 5f                	jo     14e <app_dep_rm+0x16>
  ef:	67 65 74 5f          	addr32 gs je 152 <app_dep_rm+0x1a>
  f3:	62 75                	(bad)  
  f5:	69 6c 64 5f 73 63 72 	imul   $0x69726373,0x5f(%rsp,%riz,2),%ebp
  fc:	69 
  fd:	70 74                	jo     173 <app_rel_add+0x19>
  ff:	00 61 70             	add    %ah,0x70(%rcx)
 102:	70 5f                	jo     163 <app_rel_add+0x9>
 104:	67 65 74 5f          	addr32 gs je 167 <app_rel_add+0xd>
 108:	6f                   	outsl  %ds:(%rsi),(%dx)
 109:	6e                   	outsb  %ds:(%rsi),(%dx)
 10a:	63 68 61             	movsxd 0x61(%rax),%ebp
 10d:	6e                   	outsb  %ds:(%rsi),(%dx)
 10e:	67 65 5f             	addr32 gs pop %rdi
 111:	73 63                	jae    176 <app_rel_add+0x1c>
 113:	72 69                	jb     17e <app_rel_rm+0x2>
 115:	70 74                	jo     18b <app_rel_rm+0xf>
	...

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	00 47 43             	add    %al,0x43(%rdi)
   3:	43 3a 20             	rex.XB cmp (%r8),%spl
   6:	28 55 62             	sub    %dl,0x62(%rbp)
   9:	75 6e                	jne    79 <tnt_getcwd+0x3d>
   b:	74 75                	je     82 <tnt_getcwd+0x46>
   d:	20 31                	and    %dh,(%rcx)
   f:	31 2e                	xor    %ebp,(%rsi)
  11:	34 2e                	xor    $0x2e,%al
  13:	30 2d 31 75 62 75    	xor    %ch,0x75627531(%rip)        # 7562754a <app_get_onchange_script+0x756272be>
  19:	6e                   	outsb  %ds:(%rsi),(%dx)
  1a:	74 75                	je     91 <tnt_getcwd+0x55>
  1c:	31 7e 32             	xor    %edi,0x32(%rsi)
  1f:	32 2e                	xor    (%rsi),%ch
  21:	30 34 29             	xor    %dh,(%rcx,%rbp,1)
  24:	20 31                	and    %dh,(%rcx)
  26:	31 2e                	xor    %ebp,(%rsi)
  28:	34 2e                	xor    $0x2e,%al
  2a:	30 00                	xor    %al,(%rax)

Disassembly of section .note.gnu.property:

0000000000000000 <.note.gnu.property>:
   0:	04 00                	add    $0x0,%al
   2:	00 00                	add    %al,(%rax)
   4:	10 00                	adc    %al,(%rax)
   6:	00 00                	add    %al,(%rax)
   8:	05 00 00 00 47       	add    $0x47000000,%eax
   d:	4e 55                	rex.WRX push %rbp
   f:	00 02                	add    %al,(%rdx)
  11:	00 00                	add    %al,(%rax)
  13:	c0 04 00 00          	rolb   $0x0,(%rax,%rax,1)
  17:	00 03                	add    %al,(%rbx)
  19:	00 00                	add    %al,(%rax)
  1b:	00 00                	add    %al,(%rax)
  1d:	00 00                	add    %al,(%rax)
	...

Disassembly of section .eh_frame:

0000000000000000 <.eh_frame>:
   0:	14 00                	adc    $0x0,%al
   2:	00 00                	add    %al,(%rax)
   4:	00 00                	add    %al,(%rax)
   6:	00 00                	add    %al,(%rax)
   8:	01 7a 52             	add    %edi,0x52(%rdx)
   b:	00 01                	add    %al,(%rcx)
   d:	78 10                	js     1f <.eh_frame+0x1f>
   f:	01 1b                	add    %ebx,(%rbx)
  11:	0c 07                	or     $0x7,%al
  13:	08 90 01 00 00 18    	or     %dl,0x18000001(%rax)
  19:	00 00                	add    %al,(%rax)
  1b:	00 1c 00             	add    %bl,(%rax,%rax,1)
  1e:	00 00                	add    %al,(%rax)
  20:	00 00                	add    %al,(%rax)
  22:	00 00                	add    %al,(%rax)
  24:	3c 00                	cmp    $0x0,%al
  26:	00 00                	add    %al,(%rax)
  28:	00 45 0e             	add    %al,0xe(%rbp)
  2b:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  31:	00 00                	add    %al,(%rax)
  33:	00 1c 00             	add    %bl,(%rax,%rax,1)
  36:	00 00                	add    %al,(%rax)
  38:	38 00                	cmp    %al,(%rax)
  3a:	00 00                	add    %al,(%rax)
  3c:	00 00                	add    %al,(%rax)
  3e:	00 00                	add    %al,(%rax)
  40:	b8 00 00 00 00       	mov    $0x0,%eax
  45:	45 0e                	rex.RB (bad) 
  47:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  4d:	02 af 0c 07 08 00    	add    0x8070c(%rdi),%ch
  53:	00 1c 00             	add    %bl,(%rax,%rax,1)
  56:	00 00                	add    %al,(%rax)
  58:	58                   	pop    %rax
  59:	00 00                	add    %al,(%rax)
  5b:	00 00                	add    %al,(%rax)
  5d:	00 00                	add    %al,(%rax)
  5f:	00 22                	add    %ah,(%rdx)
  61:	00 00                	add    %al,(%rax)
  63:	00 00                	add    %al,(%rax)
  65:	45 0e                	rex.RB (bad) 
  67:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  6d:	59                   	pop    %rcx
  6e:	0c 07                	or     $0x7,%al
  70:	08 00                	or     %al,(%rax)
  72:	00 00                	add    %al,(%rax)
  74:	1c 00                	sbb    $0x0,%al
  76:	00 00                	add    %al,(%rax)
  78:	78 00                	js     7a <.eh_frame+0x7a>
  7a:	00 00                	add    %al,(%rax)
  7c:	00 00                	add    %al,(%rax)
  7e:	00 00                	add    %al,(%rax)
  80:	22 00                	and    (%rax),%al
  82:	00 00                	add    %al,(%rax)
  84:	00 45 0e             	add    %al,0xe(%rbp)
  87:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  8d:	59                   	pop    %rcx
  8e:	0c 07                	or     $0x7,%al
  90:	08 00                	or     %al,(%rax)
  92:	00 00                	add    %al,(%rax)
  94:	1c 00                	sbb    $0x0,%al
  96:	00 00                	add    %al,(%rax)
  98:	98                   	cwtl   
  99:	00 00                	add    %al,(%rax)
  9b:	00 00                	add    %al,(%rax)
  9d:	00 00                	add    %al,(%rax)
  9f:	00 22                	add    %ah,(%rdx)
  a1:	00 00                	add    %al,(%rax)
  a3:	00 00                	add    %al,(%rax)
  a5:	45 0e                	rex.RB (bad) 
  a7:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  ad:	59                   	pop    %rcx
  ae:	0c 07                	or     $0x7,%al
  b0:	08 00                	or     %al,(%rax)
  b2:	00 00                	add    %al,(%rax)
  b4:	1c 00                	sbb    $0x0,%al
  b6:	00 00                	add    %al,(%rax)
  b8:	b8 00 00 00 00       	mov    $0x0,%eax
  bd:	00 00                	add    %al,(%rax)
  bf:	00 22                	add    %ah,(%rdx)
  c1:	00 00                	add    %al,(%rax)
  c3:	00 00                	add    %al,(%rax)
  c5:	45 0e                	rex.RB (bad) 
  c7:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  cd:	59                   	pop    %rcx
  ce:	0c 07                	or     $0x7,%al
  d0:	08 00                	or     %al,(%rax)
  d2:	00 00                	add    %al,(%rax)
  d4:	1c 00                	sbb    $0x0,%al
  d6:	00 00                	add    %al,(%rax)
  d8:	d8 00                	fadds  (%rax)
  da:	00 00                	add    %al,(%rax)
  dc:	00 00                	add    %al,(%rax)
  de:	00 00                	add    %al,(%rax)
  e0:	22 00                	and    (%rax),%al
  e2:	00 00                	add    %al,(%rax)
  e4:	00 45 0e             	add    %al,0xe(%rbp)
  e7:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  ed:	59                   	pop    %rcx
  ee:	0c 07                	or     $0x7,%al
  f0:	08 00                	or     %al,(%rax)
  f2:	00 00                	add    %al,(%rax)
  f4:	1c 00                	sbb    $0x0,%al
  f6:	00 00                	add    %al,(%rax)
  f8:	f8                   	clc    
  f9:	00 00                	add    %al,(%rax)
  fb:	00 00                	add    %al,(%rax)
  fd:	00 00                	add    %al,(%rax)
  ff:	00 22                	add    %ah,(%rdx)
 101:	00 00                	add    %al,(%rax)
 103:	00 00                	add    %al,(%rax)
 105:	45 0e                	rex.RB (bad) 
 107:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
 10d:	59                   	pop    %rcx
 10e:	0c 07                	or     $0x7,%al
 110:	08 00                	or     %al,(%rax)
 112:	00 00                	add    %al,(%rax)
 114:	1c 00                	sbb    $0x0,%al
 116:	00 00                	add    %al,(%rax)
 118:	18 01                	sbb    %al,(%rcx)
 11a:	00 00                	add    %al,(%rax)
 11c:	00 00                	add    %al,(%rax)
 11e:	00 00                	add    %al,(%rax)
 120:	22 00                	and    (%rax),%al
 122:	00 00                	add    %al,(%rax)
 124:	00 45 0e             	add    %al,0xe(%rbp)
 127:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
 12d:	59                   	pop    %rcx
 12e:	0c 07                	or     $0x7,%al
 130:	08 00                	or     %al,(%rax)
 132:	00 00                	add    %al,(%rax)
 134:	1c 00                	sbb    $0x0,%al
 136:	00 00                	add    %al,(%rax)
 138:	38 01                	cmp    %al,(%rcx)
 13a:	00 00                	add    %al,(%rax)
 13c:	00 00                	add    %al,(%rax)
 13e:	00 00                	add    %al,(%rax)
 140:	22 00                	and    (%rax),%al
 142:	00 00                	add    %al,(%rax)
 144:	00 45 0e             	add    %al,0xe(%rbp)
 147:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
 14d:	59                   	pop    %rcx
 14e:	0c 07                	or     $0x7,%al
 150:	08 00                	or     %al,(%rax)
 152:	00 00                	add    %al,(%rax)
 154:	1c 00                	sbb    $0x0,%al
 156:	00 00                	add    %al,(%rax)
 158:	58                   	pop    %rax
 159:	01 00                	add    %eax,(%rax)
 15b:	00 00                	add    %al,(%rax)
 15d:	00 00                	add    %al,(%rax)
 15f:	00 22                	add    %ah,(%rdx)
 161:	00 00                	add    %al,(%rax)
 163:	00 00                	add    %al,(%rax)
 165:	45 0e                	rex.RB (bad) 
 167:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
 16d:	59                   	pop    %rcx
 16e:	0c 07                	or     $0x7,%al
 170:	08 00                	or     %al,(%rax)
 172:	00 00                	add    %al,(%rax)
 174:	1c 00                	sbb    $0x0,%al
 176:	00 00                	add    %al,(%rax)
 178:	78 01                	js     17b <.eh_frame+0x17b>
 17a:	00 00                	add    %al,(%rax)
 17c:	00 00                	add    %al,(%rax)
 17e:	00 00                	add    %al,(%rax)
 180:	22 00                	and    (%rax),%al
 182:	00 00                	add    %al,(%rax)
 184:	00 45 0e             	add    %al,0xe(%rbp)
 187:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
 18d:	59                   	pop    %rcx
 18e:	0c 07                	or     $0x7,%al
 190:	08 00                	or     %al,(%rax)
 192:	00 00                	add    %al,(%rax)
 194:	1c 00                	sbb    $0x0,%al
 196:	00 00                	add    %al,(%rax)
 198:	98                   	cwtl   
 199:	01 00                	add    %eax,(%rax)
 19b:	00 00                	add    %al,(%rax)
 19d:	00 00                	add    %al,(%rax)
 19f:	00 22                	add    %ah,(%rdx)
 1a1:	00 00                	add    %al,(%rax)
 1a3:	00 00                	add    %al,(%rax)
 1a5:	45 0e                	rex.RB (bad) 
 1a7:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
 1ad:	59                   	pop    %rcx
 1ae:	0c 07                	or     $0x7,%al
 1b0:	08 00                	or     %al,(%rax)
 1b2:	00 00                	add    %al,(%rax)
 1b4:	1c 00                	sbb    $0x0,%al
 1b6:	00 00                	add    %al,(%rax)
 1b8:	b8 01 00 00 00       	mov    $0x1,%eax
 1bd:	00 00                	add    %al,(%rax)
 1bf:	00 22                	add    %ah,(%rdx)
 1c1:	00 00                	add    %al,(%rax)
 1c3:	00 00                	add    %al,(%rax)
 1c5:	45 0e                	rex.RB (bad) 
 1c7:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
 1cd:	59                   	pop    %rcx
 1ce:	0c 07                	or     $0x7,%al
 1d0:	08 00                	or     %al,(%rax)
 1d2:	00 00                	add    %al,(%rax)
 1d4:	20 00                	and    %al,(%rax)
 1d6:	00 00                	add    %al,(%rax)
 1d8:	d8 01                	fadds  (%rcx)
 1da:	00 00                	add    %al,(%rax)
 1dc:	00 00                	add    %al,(%rax)
 1de:	00 00                	add    %al,(%rax)
 1e0:	22 00                	and    (%rax),%al
 1e2:	00 00                	add    %al,(%rax)
 1e4:	00 45 0e             	add    %al,0xe(%rbp)
 1e7:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
 1ed:	59                   	pop    %rcx
 1ee:	0c 07                	or     $0x7,%al
 1f0:	08 00                	or     %al,(%rax)
 1f2:	00 00                	add    %al,(%rax)
 1f4:	00 00                	add    %al,(%rax)
	...
