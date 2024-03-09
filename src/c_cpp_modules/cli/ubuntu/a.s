
./build/cli:     file format elf64-x86-64


Disassembly of section .interp:

0000000000000318 <.interp>:
 318:	2f                   	(bad)  
 319:	6c                   	insb   (%dx),%es:(%rdi)
 31a:	69 62 36 34 2f 6c 64 	imul   $0x646c2f34,0x36(%rdx),%esp
 321:	2d 6c 69 6e 75       	sub    $0x756e696c,%eax
 326:	78 2d                	js     355 <__abi_tag-0x37>
 328:	78 38                	js     362 <__abi_tag-0x2a>
 32a:	36 2d 36 34 2e 73    	ss sub $0x732e3436,%eax
 330:	6f                   	outsl  %ds:(%rsi),(%dx)
 331:	2e 32 00             	cs xor (%rax),%al

Disassembly of section .note.gnu.property:

0000000000000338 <.note.gnu.property>:
 338:	04 00                	add    $0x0,%al
 33a:	00 00                	add    %al,(%rax)
 33c:	20 00                	and    %al,(%rax)
 33e:	00 00                	add    %al,(%rax)
 340:	05 00 00 00 47       	add    $0x47000000,%eax
 345:	4e 55                	rex.WRX push %rbp
 347:	00 02                	add    %al,(%rdx)
 349:	00 00                	add    %al,(%rax)
 34b:	c0 04 00 00          	rolb   $0x0,(%rax,%rax,1)
 34f:	00 03                	add    %al,(%rbx)
 351:	00 00                	add    %al,(%rax)
 353:	00 00                	add    %al,(%rax)
 355:	00 00                	add    %al,(%rax)
 357:	00 02                	add    %al,(%rdx)
 359:	80 00 c0             	addb   $0xc0,(%rax)
 35c:	04 00                	add    $0x0,%al
 35e:	00 00                	add    %al,(%rax)
 360:	01 00                	add    %eax,(%rax)
 362:	00 00                	add    %al,(%rax)
 364:	00 00                	add    %al,(%rax)
	...

Disassembly of section .note.gnu.build-id:

0000000000000368 <.note.gnu.build-id>:
 368:	04 00                	add    $0x0,%al
 36a:	00 00                	add    %al,(%rax)
 36c:	14 00                	adc    $0x0,%al
 36e:	00 00                	add    %al,(%rax)
 370:	03 00                	add    (%rax),%eax
 372:	00 00                	add    %al,(%rax)
 374:	47                   	rex.RXB
 375:	4e 55                	rex.WRX push %rbp
 377:	00 c0                	add    %al,%al
 379:	9f                   	lahf   
 37a:	e6 f0                	out    %al,$0xf0
 37c:	37                   	(bad)  
 37d:	87 ad 4a ee b3 7e    	xchg   %ebp,0x7eb3ee4a(%rbp)
 383:	65 52                	gs push %rdx
 385:	f8                   	clc    
 386:	2e bb d6 26 fc c3    	cs mov $0xc3fc26d6,%ebx

Disassembly of section .note.ABI-tag:

000000000000038c <__abi_tag>:
 38c:	04 00                	add    $0x0,%al
 38e:	00 00                	add    %al,(%rax)
 390:	10 00                	adc    %al,(%rax)
 392:	00 00                	add    %al,(%rax)
 394:	01 00                	add    %eax,(%rax)
 396:	00 00                	add    %al,(%rax)
 398:	47                   	rex.RXB
 399:	4e 55                	rex.WRX push %rbp
 39b:	00 00                	add    %al,(%rax)
 39d:	00 00                	add    %al,(%rax)
 39f:	00 03                	add    %al,(%rbx)
 3a1:	00 00                	add    %al,(%rax)
 3a3:	00 02                	add    %al,(%rdx)
 3a5:	00 00                	add    %al,(%rax)
 3a7:	00 00                	add    %al,(%rax)
 3a9:	00 00                	add    %al,(%rax)
	...

Disassembly of section .gnu.hash:

00000000000003b0 <.gnu.hash>:
 3b0:	02 00                	add    (%rax),%al
 3b2:	00 00                	add    %al,(%rax)
 3b4:	0f 00 00             	sldt   (%rax)
 3b7:	00 01                	add    %al,(%rcx)
 3b9:	00 00                	add    %al,(%rax)
 3bb:	00 06                	add    %al,(%rsi)
 3bd:	00 00                	add    %al,(%rax)
 3bf:	00 00                	add    %al,(%rax)
 3c1:	01 81 00 00 00 00    	add    %eax,0x0(%rcx)
 3c7:	02 0f                	add    (%rdi),%cl
 3c9:	00 00                	add    %al,(%rax)
 3cb:	00 10                	add    %dl,(%rax)
 3cd:	00 00                	add    %al,(%rax)
 3cf:	00 d1                	add    %dl,%cl
 3d1:	65 ce                	gs (bad) 
 3d3:	6d                   	insl   (%dx),%es:(%rdi)
 3d4:	39 f2                	cmp    %esi,%edx
 3d6:	8b                   	.byte 0x8b
 3d7:	1c                   	.byte 0x1c

Disassembly of section .dynsym:

00000000000003d8 <.dynsym>:
	...
 3f0:	10 00                	adc    %al,(%rax)
 3f2:	00 00                	add    %al,(%rax)
 3f4:	12 00                	adc    (%rax),%al
	...
 406:	00 00                	add    %al,(%rax)
 408:	5f                   	pop    %rdi
 409:	00 00                	add    %al,(%rax)
 40b:	00 12                	add    %dl,(%rdx)
	...
 41d:	00 00                	add    %al,(%rax)
 41f:	00 31                	add    %dh,(%rcx)
 421:	00 00                	add    %al,(%rax)
 423:	00 12                	add    %dl,(%rdx)
	...
 435:	00 00                	add    %al,(%rax)
 437:	00 96 00 00 00 20    	add    %dl,0x20000000(%rsi)
	...
 44d:	00 00                	add    %al,(%rax)
 44f:	00 2a                	add    %ch,(%rdx)
 451:	00 00                	add    %al,(%rax)
 453:	00 12                	add    %dl,(%rdx)
	...
 465:	00 00                	add    %al,(%rax)
 467:	00 48 00             	add    %cl,0x0(%rax)
 46a:	00 00                	add    %al,(%rax)
 46c:	12 00                	adc    (%rax),%al
	...
 47e:	00 00                	add    %al,(%rax)
 480:	22 00                	and    (%rax),%al
 482:	00 00                	add    %al,(%rax)
 484:	12 00                	adc    (%rax),%al
	...
 496:	00 00                	add    %al,(%rax)
 498:	29 00                	sub    %eax,(%rax)
 49a:	00 00                	add    %al,(%rax)
 49c:	12 00                	adc    (%rax),%al
	...
 4ae:	00 00                	add    %al,(%rax)
 4b0:	b2 00                	mov    $0x0,%dl
 4b2:	00 00                	add    %al,(%rax)
 4b4:	20 00                	and    %al,(%rax)
	...
 4c6:	00 00                	add    %al,(%rax)
 4c8:	39 00                	cmp    %eax,(%rax)
 4ca:	00 00                	add    %al,(%rax)
 4cc:	12 00                	adc    (%rax),%al
	...
 4de:	00 00                	add    %al,(%rax)
 4e0:	58                   	pop    %rax
 4e1:	00 00                	add    %al,(%rax)
 4e3:	00 12                	add    %dl,(%rdx)
	...
 4f5:	00 00                	add    %al,(%rax)
 4f7:	00 70 00             	add    %dh,0x0(%rax)
 4fa:	00 00                	add    %al,(%rax)
 4fc:	12 00                	adc    (%rax),%al
	...
 50e:	00 00                	add    %al,(%rax)
 510:	c1 00 00             	roll   $0x0,(%rax)
 513:	00 20                	add    %ah,(%rax)
	...
 525:	00 00                	add    %al,(%rax)
 527:	00 4f 00             	add    %cl,0x0(%rdi)
 52a:	00 00                	add    %al,(%rax)
 52c:	12 00                	adc    (%rax),%al
	...
 53e:	00 00                	add    %al,(%rax)
 540:	01 00                	add    %eax,(%rax)
 542:	00 00                	add    %al,(%rax)
 544:	22 00                	and    (%rax),%al
	...
 556:	00 00                	add    %al,(%rax)
 558:	41 00 00             	add    %al,(%r8)
 55b:	00 11                	add    %dl,(%rcx)
 55d:	00 1a                	add    %bl,(%rdx)
 55f:	00 20                	add    %ah,(%rax)
 561:	40 00 00             	rex add %al,(%rax)
 564:	00 00                	add    %al,(%rax)
 566:	00 00                	add    %al,(%rax)
 568:	08 00                	or     %al,(%rax)
 56a:	00 00                	add    %al,(%rax)
 56c:	00 00                	add    %al,(%rax)
	...

Disassembly of section .dynstr:

0000000000000570 <.dynstr>:
 570:	00 5f 5f             	add    %bl,0x5f(%rdi)
 573:	63 78 61             	movsxd 0x61(%rax),%edi
 576:	5f                   	pop    %rdi
 577:	66 69 6e 61 6c 69    	imul   $0x696c,0x61(%rsi),%bp
 57d:	7a 65                	jp     5e4 <__abi_tag+0x258>
 57f:	00 5f 5f             	add    %bl,0x5f(%rdi)
 582:	6c                   	insb   (%dx),%es:(%rdi)
 583:	69 62 63 5f 73 74 61 	imul   $0x6174735f,0x63(%rdx),%esp
 58a:	72 74                	jb     600 <__abi_tag+0x274>
 58c:	5f                   	pop    %rdi
 58d:	6d                   	insl   (%dx),%es:(%rdi)
 58e:	61                   	(bad)  
 58f:	69 6e 00 73 74 72 63 	imul   $0x63727473,0x0(%rsi),%ebp
 596:	6d                   	insl   (%dx),%es:(%rdi)
 597:	70 00                	jo     599 <__abi_tag+0x20d>
 599:	66 70 72             	data16 jo 60e <__abi_tag+0x282>
 59c:	69 6e 74 66 00 73 74 	imul   $0x74730066,0x74(%rsi),%ebp
 5a3:	72 6e                	jb     613 <__abi_tag+0x287>
 5a5:	63 6d 70             	movsxd 0x70(%rbp),%ebp
 5a8:	00 72 65             	add    %dh,0x65(%rdx)
 5ab:	61                   	(bad)  
 5ac:	6c                   	insb   (%dx),%es:(%rdi)
 5ad:	6c                   	insb   (%dx),%es:(%rdi)
 5ae:	6f                   	outsl  %ds:(%rsi),(%dx)
 5af:	63 00                	movsxd (%rax),%eax
 5b1:	73 74                	jae    627 <__abi_tag+0x29b>
 5b3:	64 65 72 72          	fs gs jb 629 <__abi_tag+0x29d>
 5b7:	00 67 65             	add    %ah,0x65(%rdi)
 5ba:	74 63                	je     61f <__abi_tag+0x293>
 5bc:	77 64                	ja     622 <__abi_tag+0x296>
 5be:	00 73 74             	add    %dh,0x74(%rbx)
 5c1:	72 65                	jb     628 <__abi_tag+0x29c>
 5c3:	72 72                	jb     637 <__abi_tag+0x2ab>
 5c5:	6f                   	outsl  %ds:(%rsi),(%dx)
 5c6:	72 00                	jb     5c8 <__abi_tag+0x23c>
 5c8:	73 74                	jae    63e <__abi_tag+0x2b2>
 5ca:	72 63                	jb     62f <__abi_tag+0x2a3>
 5cc:	61                   	(bad)  
 5cd:	74 00                	je     5cf <__abi_tag+0x243>
 5cf:	5f                   	pop    %rdi
 5d0:	5f                   	pop    %rdi
 5d1:	65 72 72             	gs jb  646 <__abi_tag+0x2ba>
 5d4:	6e                   	outsb  %ds:(%rsi),(%dx)
 5d5:	6f                   	outsl  %ds:(%rsi),(%dx)
 5d6:	5f                   	pop    %rdi
 5d7:	6c                   	insb   (%dx),%es:(%rdi)
 5d8:	6f                   	outsl  %ds:(%rsi),(%dx)
 5d9:	63 61 74             	movsxd 0x74(%rcx),%esp
 5dc:	69 6f 6e 00 65 78 69 	imul   $0x69786500,0x6e(%rdi),%ebp
 5e3:	74 00                	je     5e5 <__abi_tag+0x259>
 5e5:	6c                   	insb   (%dx),%es:(%rdi)
 5e6:	69 62 63 2e 73 6f 2e 	imul   $0x2e6f732e,0x63(%rdx),%esp
 5ed:	36 00 47 4c          	ss add %al,0x4c(%rdi)
 5f1:	49                   	rex.WB
 5f2:	42                   	rex.X
 5f3:	43 5f                	rex.XB pop %r15
 5f5:	32 2e                	xor    (%rsi),%ch
 5f7:	32 2e                	xor    (%rsi),%ch
 5f9:	35 00 47 4c 49       	xor    $0x494c4700,%eax
 5fe:	42                   	rex.X
 5ff:	43 5f                	rex.XB pop %r15
 601:	32 2e                	xor    (%rsi),%ch
 603:	33 34 00             	xor    (%rax,%rax,1),%esi
 606:	5f                   	pop    %rdi
 607:	49 54                	rex.WB push %r12
 609:	4d 5f                	rex.WRB pop %r15
 60b:	64 65 72 65          	fs gs jb 674 <__abi_tag+0x2e8>
 60f:	67 69 73 74 65 72 54 	imul   $0x4d547265,0x74(%ebx),%esi
 616:	4d 
 617:	43 6c                	rex.XB insb (%dx),%es:(%rdi)
 619:	6f                   	outsl  %ds:(%rsi),(%dx)
 61a:	6e                   	outsb  %ds:(%rsi),(%dx)
 61b:	65 54                	gs push %rsp
 61d:	61                   	(bad)  
 61e:	62                   	(bad)  
 61f:	6c                   	insb   (%dx),%es:(%rdi)
 620:	65 00 5f 5f          	add    %bl,%gs:0x5f(%rdi)
 624:	67 6d                	insl   (%dx),%es:(%edi)
 626:	6f                   	outsl  %ds:(%rsi),(%dx)
 627:	6e                   	outsb  %ds:(%rsi),(%dx)
 628:	5f                   	pop    %rdi
 629:	73 74                	jae    69f <__abi_tag+0x313>
 62b:	61                   	(bad)  
 62c:	72 74                	jb     6a2 <__abi_tag+0x316>
 62e:	5f                   	pop    %rdi
 62f:	5f                   	pop    %rdi
 630:	00 5f 49             	add    %bl,0x49(%rdi)
 633:	54                   	push   %rsp
 634:	4d 5f                	rex.WRB pop %r15
 636:	72 65                	jb     69d <__abi_tag+0x311>
 638:	67 69 73 74 65 72 54 	imul   $0x4d547265,0x74(%ebx),%esi
 63f:	4d 
 640:	43 6c                	rex.XB insb (%dx),%es:(%rdi)
 642:	6f                   	outsl  %ds:(%rsi),(%dx)
 643:	6e                   	outsb  %ds:(%rsi),(%dx)
 644:	65 54                	gs push %rsp
 646:	61                   	(bad)  
 647:	62                   	.byte 0x62
 648:	6c                   	insb   (%dx),%es:(%rdi)
 649:	65                   	gs
	...

Disassembly of section .gnu.version:

000000000000064c <.gnu.version>:
 64c:	00 00                	add    %al,(%rax)
 64e:	02 00                	add    (%rax),%al
 650:	03 00                	add    (%rax),%eax
 652:	03 00                	add    (%rax),%eax
 654:	01 00                	add    %eax,(%rax)
 656:	03 00                	add    (%rax),%eax
 658:	03 00                	add    (%rax),%eax
 65a:	03 00                	add    (%rax),%eax
 65c:	03 00                	add    (%rax),%eax
 65e:	01 00                	add    %eax,(%rax)
 660:	03 00                	add    (%rax),%eax
 662:	03 00                	add    (%rax),%eax
 664:	03 00                	add    (%rax),%eax
 666:	01 00                	add    %eax,(%rax)
 668:	03 00                	add    (%rax),%eax
 66a:	03 00                	add    (%rax),%eax
 66c:	03 00                	add    (%rax),%eax

Disassembly of section .gnu.version_r:

0000000000000670 <.gnu.version_r>:
 670:	01 00                	add    %eax,(%rax)
 672:	02 00                	add    (%rax),%al
 674:	75 00                	jne    676 <__abi_tag+0x2ea>
 676:	00 00                	add    %al,(%rax)
 678:	10 00                	adc    %al,(%rax)
 67a:	00 00                	add    %al,(%rax)
 67c:	00 00                	add    %al,(%rax)
 67e:	00 00                	add    %al,(%rax)
 680:	75 1a                	jne    69c <__abi_tag+0x310>
 682:	69 09 00 00 03 00    	imul   $0x30000,(%rcx),%ecx
 688:	7f 00                	jg     68a <__abi_tag+0x2fe>
 68a:	00 00                	add    %al,(%rax)
 68c:	10 00                	adc    %al,(%rax)
 68e:	00 00                	add    %al,(%rax)
 690:	b4 91                	mov    $0x91,%ah
 692:	96                   	xchg   %eax,%esi
 693:	06                   	(bad)  
 694:	00 00                	add    %al,(%rax)
 696:	02 00                	add    (%rax),%al
 698:	8b 00                	mov    (%rax),%eax
 69a:	00 00                	add    %al,(%rax)
 69c:	00 00                	add    %al,(%rax)
	...

Disassembly of section .rela.dyn:

00000000000006a0 <.rela.dyn>:
 6a0:	70 3d                	jo     6df <__abi_tag+0x353>
 6a2:	00 00                	add    %al,(%rax)
 6a4:	00 00                	add    %al,(%rax)
 6a6:	00 00                	add    %al,(%rax)
 6a8:	08 00                	or     %al,(%rax)
 6aa:	00 00                	add    %al,(%rax)
 6ac:	00 00                	add    %al,(%rax)
 6ae:	00 00                	add    %al,(%rax)
 6b0:	60                   	(bad)  
 6b1:	12 00                	adc    (%rax),%al
 6b3:	00 00                	add    %al,(%rax)
 6b5:	00 00                	add    %al,(%rax)
 6b7:	00 78 3d             	add    %bh,0x3d(%rax)
 6ba:	00 00                	add    %al,(%rax)
 6bc:	00 00                	add    %al,(%rax)
 6be:	00 00                	add    %al,(%rax)
 6c0:	08 00                	or     %al,(%rax)
 6c2:	00 00                	add    %al,(%rax)
 6c4:	00 00                	add    %al,(%rax)
 6c6:	00 00                	add    %al,(%rax)
 6c8:	20 12                	and    %dl,(%rdx)
 6ca:	00 00                	add    %al,(%rax)
 6cc:	00 00                	add    %al,(%rax)
 6ce:	00 00                	add    %al,(%rax)
 6d0:	08 40 00             	or     %al,0x0(%rax)
 6d3:	00 00                	add    %al,(%rax)
 6d5:	00 00                	add    %al,(%rax)
 6d7:	00 08                	add    %cl,(%rax)
 6d9:	00 00                	add    %al,(%rax)
 6db:	00 00                	add    %al,(%rax)
 6dd:	00 00                	add    %al,(%rax)
 6df:	00 08                	add    %cl,(%rax)
 6e1:	40 00 00             	rex add %al,(%rax)
 6e4:	00 00                	add    %al,(%rax)
 6e6:	00 00                	add    %al,(%rax)
 6e8:	d8 3f                	fdivrs (%rdi)
 6ea:	00 00                	add    %al,(%rax)
 6ec:	00 00                	add    %al,(%rax)
 6ee:	00 00                	add    %al,(%rax)
 6f0:	06                   	(bad)  
 6f1:	00 00                	add    %al,(%rax)
 6f3:	00 01                	add    %al,(%rcx)
	...
 6fd:	00 00                	add    %al,(%rax)
 6ff:	00 e0                	add    %ah,%al
 701:	3f                   	(bad)  
 702:	00 00                	add    %al,(%rax)
 704:	00 00                	add    %al,(%rax)
 706:	00 00                	add    %al,(%rax)
 708:	06                   	(bad)  
 709:	00 00                	add    %al,(%rax)
 70b:	00 04 00             	add    %al,(%rax,%rax,1)
	...
 716:	00 00                	add    %al,(%rax)
 718:	e8 3f 00 00 00       	call   75c <__abi_tag+0x3d0>
 71d:	00 00                	add    %al,(%rax)
 71f:	00 06                	add    %al,(%rsi)
 721:	00 00                	add    %al,(%rax)
 723:	00 09                	add    %cl,(%rcx)
	...
 72d:	00 00                	add    %al,(%rax)
 72f:	00 f0                	add    %dh,%al
 731:	3f                   	(bad)  
 732:	00 00                	add    %al,(%rax)
 734:	00 00                	add    %al,(%rax)
 736:	00 00                	add    %al,(%rax)
 738:	06                   	(bad)  
 739:	00 00                	add    %al,(%rax)
 73b:	00 0d 00 00 00 00    	add    %cl,0x0(%rip)        # 741 <__abi_tag+0x3b5>
 741:	00 00                	add    %al,(%rax)
 743:	00 00                	add    %al,(%rax)
 745:	00 00                	add    %al,(%rax)
 747:	00 f8                	add    %bh,%al
 749:	3f                   	(bad)  
 74a:	00 00                	add    %al,(%rax)
 74c:	00 00                	add    %al,(%rax)
 74e:	00 00                	add    %al,(%rax)
 750:	06                   	(bad)  
 751:	00 00                	add    %al,(%rax)
 753:	00 0f                	add    %cl,(%rdi)
	...
 75d:	00 00                	add    %al,(%rax)
 75f:	00 20                	add    %ah,(%rax)
 761:	40 00 00             	rex add %al,(%rax)
 764:	00 00                	add    %al,(%rax)
 766:	00 00                	add    %al,(%rax)
 768:	05 00 00 00 10       	add    $0x10000000,%eax
	...

Disassembly of section .rela.plt:

0000000000000778 <.rela.plt>:
 778:	88 3f                	mov    %bh,(%rdi)
 77a:	00 00                	add    %al,(%rax)
 77c:	00 00                	add    %al,(%rax)
 77e:	00 00                	add    %al,(%rax)
 780:	07                   	(bad)  
 781:	00 00                	add    %al,(%rax)
 783:	00 02                	add    %al,(%rdx)
	...
 78d:	00 00                	add    %al,(%rax)
 78f:	00 90 3f 00 00 00    	add    %dl,0x3f(%rax)
 795:	00 00                	add    %al,(%rax)
 797:	00 07                	add    %al,(%rdi)
 799:	00 00                	add    %al,(%rax)
 79b:	00 03                	add    %al,(%rbx)
	...
 7a5:	00 00                	add    %al,(%rax)
 7a7:	00 98 3f 00 00 00    	add    %bl,0x3f(%rax)
 7ad:	00 00                	add    %al,(%rax)
 7af:	00 07                	add    %al,(%rdi)
 7b1:	00 00                	add    %al,(%rax)
 7b3:	00 05 00 00 00 00    	add    %al,0x0(%rip)        # 7b9 <__abi_tag+0x42d>
 7b9:	00 00                	add    %al,(%rax)
 7bb:	00 00                	add    %al,(%rax)
 7bd:	00 00                	add    %al,(%rax)
 7bf:	00 a0 3f 00 00 00    	add    %ah,0x3f(%rax)
 7c5:	00 00                	add    %al,(%rax)
 7c7:	00 07                	add    %al,(%rdi)
 7c9:	00 00                	add    %al,(%rax)
 7cb:	00 06                	add    %al,(%rsi)
	...
 7d5:	00 00                	add    %al,(%rax)
 7d7:	00 a8 3f 00 00 00    	add    %ch,0x3f(%rax)
 7dd:	00 00                	add    %al,(%rax)
 7df:	00 07                	add    %al,(%rdi)
 7e1:	00 00                	add    %al,(%rax)
 7e3:	00 07                	add    %al,(%rdi)
	...
 7ed:	00 00                	add    %al,(%rax)
 7ef:	00 b0 3f 00 00 00    	add    %dh,0x3f(%rax)
 7f5:	00 00                	add    %al,(%rax)
 7f7:	00 07                	add    %al,(%rdi)
 7f9:	00 00                	add    %al,(%rax)
 7fb:	00 08                	add    %cl,(%rax)
	...
 805:	00 00                	add    %al,(%rax)
 807:	00 b8 3f 00 00 00    	add    %bh,0x3f(%rax)
 80d:	00 00                	add    %al,(%rax)
 80f:	00 07                	add    %al,(%rdi)
 811:	00 00                	add    %al,(%rax)
 813:	00 0a                	add    %cl,(%rdx)
	...
 81d:	00 00                	add    %al,(%rax)
 81f:	00 c0                	add    %al,%al
 821:	3f                   	(bad)  
 822:	00 00                	add    %al,(%rax)
 824:	00 00                	add    %al,(%rax)
 826:	00 00                	add    %al,(%rax)
 828:	07                   	(bad)  
 829:	00 00                	add    %al,(%rax)
 82b:	00 0b                	add    %cl,(%rbx)
	...
 835:	00 00                	add    %al,(%rax)
 837:	00 c8                	add    %cl,%al
 839:	3f                   	(bad)  
 83a:	00 00                	add    %al,(%rax)
 83c:	00 00                	add    %al,(%rax)
 83e:	00 00                	add    %al,(%rax)
 840:	07                   	(bad)  
 841:	00 00                	add    %al,(%rax)
 843:	00 0c 00             	add    %cl,(%rax,%rax,1)
	...
 84e:	00 00                	add    %al,(%rax)
 850:	d0 3f                	sarb   (%rdi)
 852:	00 00                	add    %al,(%rax)
 854:	00 00                	add    %al,(%rax)
 856:	00 00                	add    %al,(%rax)
 858:	07                   	(bad)  
 859:	00 00                	add    %al,(%rax)
 85b:	00 0e                	add    %cl,(%rsi)
	...

Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 52 2f 00 00    	push   0x2f52(%rip)        # 3f78 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 53 2f 00 00 	bnd jmp *0x2f53(%rip)        # 3f80 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	push   $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    104f:	90                   	nop
    1050:	f3 0f 1e fa          	endbr64 
    1054:	68 02 00 00 00       	push   $0x2
    1059:	f2 e9 c1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    105f:	90                   	nop
    1060:	f3 0f 1e fa          	endbr64 
    1064:	68 03 00 00 00       	push   $0x3
    1069:	f2 e9 b1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    106f:	90                   	nop
    1070:	f3 0f 1e fa          	endbr64 
    1074:	68 04 00 00 00       	push   $0x4
    1079:	f2 e9 a1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    107f:	90                   	nop
    1080:	f3 0f 1e fa          	endbr64 
    1084:	68 05 00 00 00       	push   $0x5
    1089:	f2 e9 91 ff ff ff    	bnd jmp 1020 <_init+0x20>
    108f:	90                   	nop
    1090:	f3 0f 1e fa          	endbr64 
    1094:	68 06 00 00 00       	push   $0x6
    1099:	f2 e9 81 ff ff ff    	bnd jmp 1020 <_init+0x20>
    109f:	90                   	nop
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	68 07 00 00 00       	push   $0x7
    10a9:	f2 e9 71 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10af:	90                   	nop
    10b0:	f3 0f 1e fa          	endbr64 
    10b4:	68 08 00 00 00       	push   $0x8
    10b9:	f2 e9 61 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10bf:	90                   	nop
    10c0:	f3 0f 1e fa          	endbr64 
    10c4:	68 09 00 00 00       	push   $0x9
    10c9:	f2 e9 51 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10cf:	90                   	nop

Disassembly of section .plt.got:

00000000000010d0 <__cxa_finalize@plt>:
    10d0:	f3 0f 1e fa          	endbr64 
    10d4:	f2 ff 25 1d 2f 00 00 	bnd jmp *0x2f1d(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    10db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

00000000000010e0 <__errno_location@plt>:
    10e0:	f3 0f 1e fa          	endbr64 
    10e4:	f2 ff 25 9d 2e 00 00 	bnd jmp *0x2e9d(%rip)        # 3f88 <__errno_location@GLIBC_2.2.5>
    10eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010f0 <strncmp@plt>:
    10f0:	f3 0f 1e fa          	endbr64 
    10f4:	f2 ff 25 95 2e 00 00 	bnd jmp *0x2e95(%rip)        # 3f90 <strncmp@GLIBC_2.2.5>
    10fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001100 <printf@plt>:
    1100:	f3 0f 1e fa          	endbr64 
    1104:	f2 ff 25 8d 2e 00 00 	bnd jmp *0x2e8d(%rip)        # 3f98 <printf@GLIBC_2.2.5>
    110b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001110 <getcwd@plt>:
    1110:	f3 0f 1e fa          	endbr64 
    1114:	f2 ff 25 85 2e 00 00 	bnd jmp *0x2e85(%rip)        # 3fa0 <getcwd@GLIBC_2.2.5>
    111b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001120 <strcmp@plt>:
    1120:	f3 0f 1e fa          	endbr64 
    1124:	f2 ff 25 7d 2e 00 00 	bnd jmp *0x2e7d(%rip)        # 3fa8 <strcmp@GLIBC_2.2.5>
    112b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001130 <fprintf@plt>:
    1130:	f3 0f 1e fa          	endbr64 
    1134:	f2 ff 25 75 2e 00 00 	bnd jmp *0x2e75(%rip)        # 3fb0 <fprintf@GLIBC_2.2.5>
    113b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001140 <realloc@plt>:
    1140:	f3 0f 1e fa          	endbr64 
    1144:	f2 ff 25 6d 2e 00 00 	bnd jmp *0x2e6d(%rip)        # 3fb8 <realloc@GLIBC_2.2.5>
    114b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001150 <strcat@plt>:
    1150:	f3 0f 1e fa          	endbr64 
    1154:	f2 ff 25 65 2e 00 00 	bnd jmp *0x2e65(%rip)        # 3fc0 <strcat@GLIBC_2.2.5>
    115b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001160 <exit@plt>:
    1160:	f3 0f 1e fa          	endbr64 
    1164:	f2 ff 25 5d 2e 00 00 	bnd jmp *0x2e5d(%rip)        # 3fc8 <exit@GLIBC_2.2.5>
    116b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001170 <strerror@plt>:
    1170:	f3 0f 1e fa          	endbr64 
    1174:	f2 ff 25 55 2e 00 00 	bnd jmp *0x2e55(%rip)        # 3fd0 <strerror@GLIBC_2.2.5>
    117b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001180 <_start>:
    1180:	f3 0f 1e fa          	endbr64 
    1184:	31 ed                	xor    %ebp,%ebp
    1186:	49 89 d1             	mov    %rdx,%r9
    1189:	5e                   	pop    %rsi
    118a:	48 89 e2             	mov    %rsp,%rdx
    118d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1191:	50                   	push   %rax
    1192:	54                   	push   %rsp
    1193:	45 31 c0             	xor    %r8d,%r8d
    1196:	31 c9                	xor    %ecx,%ecx
    1198:	48 8d 3d ca 00 00 00 	lea    0xca(%rip),%rdi        # 1269 <main>
    119f:	ff 15 33 2e 00 00    	call   *0x2e33(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    11a5:	f4                   	hlt    
    11a6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    11ad:	00 00 00 

00000000000011b0 <deregister_tm_clones>:
    11b0:	48 8d 3d 59 2e 00 00 	lea    0x2e59(%rip),%rdi        # 4010 <__TMC_END__>
    11b7:	48 8d 05 52 2e 00 00 	lea    0x2e52(%rip),%rax        # 4010 <__TMC_END__>
    11be:	48 39 f8             	cmp    %rdi,%rax
    11c1:	74 15                	je     11d8 <deregister_tm_clones+0x28>
    11c3:	48 8b 05 16 2e 00 00 	mov    0x2e16(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    11ca:	48 85 c0             	test   %rax,%rax
    11cd:	74 09                	je     11d8 <deregister_tm_clones+0x28>
    11cf:	ff e0                	jmp    *%rax
    11d1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    11d8:	c3                   	ret    
    11d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000011e0 <register_tm_clones>:
    11e0:	48 8d 3d 29 2e 00 00 	lea    0x2e29(%rip),%rdi        # 4010 <__TMC_END__>
    11e7:	48 8d 35 22 2e 00 00 	lea    0x2e22(%rip),%rsi        # 4010 <__TMC_END__>
    11ee:	48 29 fe             	sub    %rdi,%rsi
    11f1:	48 89 f0             	mov    %rsi,%rax
    11f4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    11f8:	48 c1 f8 03          	sar    $0x3,%rax
    11fc:	48 01 c6             	add    %rax,%rsi
    11ff:	48 d1 fe             	sar    %rsi
    1202:	74 14                	je     1218 <register_tm_clones+0x38>
    1204:	48 8b 05 e5 2d 00 00 	mov    0x2de5(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    120b:	48 85 c0             	test   %rax,%rax
    120e:	74 08                	je     1218 <register_tm_clones+0x38>
    1210:	ff e0                	jmp    *%rax
    1212:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1218:	c3                   	ret    
    1219:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001220 <__do_global_dtors_aux>:
    1220:	f3 0f 1e fa          	endbr64 
    1224:	80 3d fd 2d 00 00 00 	cmpb   $0x0,0x2dfd(%rip)        # 4028 <completed.0>
    122b:	75 2b                	jne    1258 <__do_global_dtors_aux+0x38>
    122d:	55                   	push   %rbp
    122e:	48 83 3d c2 2d 00 00 	cmpq   $0x0,0x2dc2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1235:	00 
    1236:	48 89 e5             	mov    %rsp,%rbp
    1239:	74 0c                	je     1247 <__do_global_dtors_aux+0x27>
    123b:	48 8b 3d c6 2d 00 00 	mov    0x2dc6(%rip),%rdi        # 4008 <__dso_handle>
    1242:	e8 89 fe ff ff       	call   10d0 <__cxa_finalize@plt>
    1247:	e8 64 ff ff ff       	call   11b0 <deregister_tm_clones>
    124c:	c6 05 d5 2d 00 00 01 	movb   $0x1,0x2dd5(%rip)        # 4028 <completed.0>
    1253:	5d                   	pop    %rbp
    1254:	c3                   	ret    
    1255:	0f 1f 00             	nopl   (%rax)
    1258:	c3                   	ret    
    1259:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001260 <frame_dummy>:
    1260:	f3 0f 1e fa          	endbr64 
    1264:	e9 77 ff ff ff       	jmp    11e0 <register_tm_clones>

0000000000001269 <main>:
    1269:	f3 0f 1e fa          	endbr64 
    126d:	55                   	push   %rbp
    126e:	48 89 e5             	mov    %rsp,%rbp
    1271:	48 83 ec 20          	sub    $0x20,%rsp
    1275:	89 7d ec             	mov    %edi,-0x14(%rbp)
    1278:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    127c:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
    1280:	8b 4d ec             	mov    -0x14(%rbp),%ecx
    1283:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1287:	89 ce                	mov    %ecx,%esi
    1289:	48 89 c7             	mov    %rax,%rdi
    128c:	e8 f6 00 00 00       	call   1387 <tnt_app_main_cmd>
    1291:	c9                   	leave  
    1292:	c3                   	ret    

0000000000001293 <app_exit_error>:
    1293:	f3 0f 1e fa          	endbr64 
    1297:	55                   	push   %rbp
    1298:	48 89 e5             	mov    %rsp,%rbp
    129b:	48 83 ec 10          	sub    $0x10,%rsp
    129f:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    12a3:	48 8b 05 76 2d 00 00 	mov    0x2d76(%rip),%rax        # 4020 <stderr@GLIBC_2.2.5>
    12aa:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    12ae:	48 8d 0d 53 0d 00 00 	lea    0xd53(%rip),%rcx        # 2008 <_IO_stdin_used+0x8>
    12b5:	48 89 ce             	mov    %rcx,%rsi
    12b8:	48 89 c7             	mov    %rax,%rdi
    12bb:	b8 00 00 00 00       	mov    $0x0,%eax
    12c0:	e8 6b fe ff ff       	call   1130 <fprintf@plt>
    12c5:	bf ff ff ff ff       	mov    $0xffffffff,%edi
    12ca:	e8 91 fe ff ff       	call   1160 <exit@plt>

00000000000012cf <tnt_getcwd>:
    12cf:	f3 0f 1e fa          	endbr64 
    12d3:	55                   	push   %rbp
    12d4:	48 89 e5             	mov    %rsp,%rbp
    12d7:	48 83 ec 20          	sub    $0x20,%rsp
    12db:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
    12e2:	00 
    12e3:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
    12ea:	00 
    12eb:	48 c7 45 f0 00 01 00 	movq   $0x100,-0x10(%rbp)
    12f2:	00 
    12f3:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
    12f7:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    12fb:	48 89 d6             	mov    %rdx,%rsi
    12fe:	48 89 c7             	mov    %rax,%rdi
    1301:	e8 3a fe ff ff       	call   1140 <realloc@plt>
    1306:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    130a:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
    130f:	75 0f                	jne    1320 <tnt_getcwd+0x51>
    1311:	48 8d 05 00 0d 00 00 	lea    0xd00(%rip),%rax        # 2018 <_IO_stdin_used+0x18>
    1318:	48 89 c7             	mov    %rax,%rdi
    131b:	e8 73 ff ff ff       	call   1293 <app_exit_error>
    1320:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
    1324:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1328:	48 89 d6             	mov    %rdx,%rsi
    132b:	48 89 c7             	mov    %rax,%rdi
    132e:	e8 dd fd ff ff       	call   1110 <getcwd@plt>
    1333:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1337:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
    133c:	75 34                	jne    1372 <tnt_getcwd+0xa3>
    133e:	e8 9d fd ff ff       	call   10e0 <__errno_location@plt>
    1343:	8b 00                	mov    (%rax),%eax
    1345:	83 f8 22             	cmp    $0x22,%eax
    1348:	74 28                	je     1372 <tnt_getcwd+0xa3>
    134a:	e8 91 fd ff ff       	call   10e0 <__errno_location@plt>
    134f:	8b 00                	mov    (%rax),%eax
    1351:	89 c7                	mov    %eax,%edi
    1353:	e8 18 fe ff ff       	call   1170 <strerror@plt>
    1358:	48 89 c6             	mov    %rax,%rsi
    135b:	48 8d 05 e6 0c 00 00 	lea    0xce6(%rip),%rax        # 2048 <_IO_stdin_used+0x48>
    1362:	48 89 c7             	mov    %rax,%rdi
    1365:	e8 e6 fd ff ff       	call   1150 <strcat@plt>
    136a:	48 89 c7             	mov    %rax,%rdi
    136d:	e8 21 ff ff ff       	call   1293 <app_exit_error>
    1372:	48 d1 65 f0          	shlq   -0x10(%rbp)
    1376:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
    137b:	0f 84 72 ff ff ff    	je     12f3 <tnt_getcwd+0x24>
    1381:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1385:	c9                   	leave  
    1386:	c3                   	ret    

0000000000001387 <tnt_app_main_cmd>:
    1387:	f3 0f 1e fa          	endbr64 
    138b:	55                   	push   %rbp
    138c:	48 89 e5             	mov    %rsp,%rbp
    138f:	48 83 ec 30          	sub    $0x30,%rsp
    1393:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    1397:	89 75 e4             	mov    %esi,-0x1c(%rbp)
    139a:	48 89 55 d8          	mov    %rdx,-0x28(%rbp)
    139e:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
    13a5:	00 
    13a6:	b8 00 00 00 00       	mov    $0x0,%eax
    13ab:	e8 1f ff ff ff       	call   12cf <tnt_getcwd>
    13b0:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    13b4:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    13b8:	48 89 c6             	mov    %rax,%rsi
    13bb:	48 8d 05 99 0c 00 00 	lea    0xc99(%rip),%rax        # 205b <_IO_stdin_used+0x5b>
    13c2:	48 89 c7             	mov    %rax,%rdi
    13c5:	b8 00 00 00 00       	mov    $0x0,%eax
    13ca:	e8 31 fd ff ff       	call   1100 <printf@plt>
    13cf:	be 12 00 00 00       	mov    $0x12,%esi
    13d4:	48 8d 05 99 0c 00 00 	lea    0xc99(%rip),%rax        # 2074 <_IO_stdin_used+0x74>
    13db:	48 89 c7             	mov    %rax,%rdi
    13de:	b8 00 00 00 00       	mov    $0x0,%eax
    13e3:	e8 18 fd ff ff       	call   1100 <printf@plt>
    13e8:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
    13ef:	00 
    13f0:	e9 4e 01 00 00       	jmp    1543 <tnt_app_main_cmd+0x1bc>
    13f5:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    13f9:	0f b6 00             	movzbl (%rax),%eax
    13fc:	3c 2d                	cmp    $0x2d,%al
    13fe:	74 0a                	je     140a <tnt_app_main_cmd+0x83>
    1400:	48 83 6d d8 08       	subq   $0x8,-0x28(%rbp)
    1405:	e9 54 01 00 00       	jmp    155e <tnt_app_main_cmd+0x1d7>
    140a:	48 83 45 f8 01       	addq   $0x1,-0x8(%rbp)
    140f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1413:	0f b6 00             	movzbl (%rax),%eax
    1416:	3c 2d                	cmp    $0x2d,%al
    1418:	0f 85 8c 00 00 00    	jne    14aa <tnt_app_main_cmd+0x123>
    141e:	48 83 45 f8 01       	addq   $0x1,-0x8(%rbp)
    1423:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1427:	48 8d 15 4f 0c 00 00 	lea    0xc4f(%rip),%rdx        # 207d <_IO_stdin_used+0x7d>
    142e:	48 89 d6             	mov    %rdx,%rsi
    1431:	48 89 c7             	mov    %rax,%rdi
    1434:	e8 e7 fc ff ff       	call   1120 <strcmp@plt>
    1439:	85 c0                	test   %eax,%eax
    143b:	75 10                	jne    144d <tnt_app_main_cmd+0xc6>
    143d:	48 8d 05 41 0c 00 00 	lea    0xc41(%rip),%rax        # 2085 <_IO_stdin_used+0x85>
    1444:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    1448:	e9 66 01 00 00       	jmp    15b3 <tnt_app_main_cmd+0x22c>
    144d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1451:	48 8d 15 39 0c 00 00 	lea    0xc39(%rip),%rdx        # 2091 <_IO_stdin_used+0x91>
    1458:	48 89 d6             	mov    %rdx,%rsi
    145b:	48 89 c7             	mov    %rax,%rdi
    145e:	e8 bd fc ff ff       	call   1120 <strcmp@plt>
    1463:	85 c0                	test   %eax,%eax
    1465:	75 10                	jne    1477 <tnt_app_main_cmd+0xf0>
    1467:	48 8d 05 28 0c 00 00 	lea    0xc28(%rip),%rax        # 2096 <_IO_stdin_used+0x96>
    146e:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    1472:	e9 3c 01 00 00       	jmp    15b3 <tnt_app_main_cmd+0x22c>
    1477:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    147b:	ba 12 00 00 00       	mov    $0x12,%edx
    1480:	48 8d 0d 18 0c 00 00 	lea    0xc18(%rip),%rcx        # 209f <_IO_stdin_used+0x9f>
    1487:	48 89 ce             	mov    %rcx,%rsi
    148a:	48 89 c7             	mov    %rax,%rdi
    148d:	e8 5e fc ff ff       	call   10f0 <strncmp@plt>
    1492:	85 c0                	test   %eax,%eax
    1494:	0f 85 a9 00 00 00    	jne    1543 <tnt_app_main_cmd+0x1bc>
    149a:	48 8d 05 f5 0b 00 00 	lea    0xbf5(%rip),%rax        # 2096 <_IO_stdin_used+0x96>
    14a1:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    14a5:	e9 09 01 00 00       	jmp    15b3 <tnt_app_main_cmd+0x22c>
    14aa:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    14ae:	48 8d 15 fd 0b 00 00 	lea    0xbfd(%rip),%rdx        # 20b2 <_IO_stdin_used+0xb2>
    14b5:	48 89 d6             	mov    %rdx,%rsi
    14b8:	48 89 c7             	mov    %rax,%rdi
    14bb:	e8 60 fc ff ff       	call   1120 <strcmp@plt>
    14c0:	85 c0                	test   %eax,%eax
    14c2:	75 10                	jne    14d4 <tnt_app_main_cmd+0x14d>
    14c4:	48 8d 05 ba 0b 00 00 	lea    0xbba(%rip),%rax        # 2085 <_IO_stdin_used+0x85>
    14cb:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    14cf:	e9 df 00 00 00       	jmp    15b3 <tnt_app_main_cmd+0x22c>
    14d4:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    14d8:	48 8d 15 d5 0b 00 00 	lea    0xbd5(%rip),%rdx        # 20b4 <_IO_stdin_used+0xb4>
    14df:	48 89 d6             	mov    %rdx,%rsi
    14e2:	48 89 c7             	mov    %rax,%rdi
    14e5:	e8 36 fc ff ff       	call   1120 <strcmp@plt>
    14ea:	85 c0                	test   %eax,%eax
    14ec:	75 10                	jne    14fe <tnt_app_main_cmd+0x177>
    14ee:	48 8d 05 a1 0b 00 00 	lea    0xba1(%rip),%rax        # 2096 <_IO_stdin_used+0x96>
    14f5:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    14f9:	e9 b5 00 00 00       	jmp    15b3 <tnt_app_main_cmd+0x22c>
    14fe:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1502:	48 8d 15 ad 0b 00 00 	lea    0xbad(%rip),%rdx        # 20b6 <_IO_stdin_used+0xb6>
    1509:	48 89 d6             	mov    %rdx,%rsi
    150c:	48 89 c7             	mov    %rax,%rdi
    150f:	e8 0c fc ff ff       	call   1120 <strcmp@plt>
    1514:	85 c0                	test   %eax,%eax
    1516:	75 2b                	jne    1543 <tnt_app_main_cmd+0x1bc>
    1518:	48 83 45 d8 08       	addq   $0x8,-0x28(%rbp)
    151d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1521:	48 8b 00             	mov    (%rax),%rax
    1524:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1528:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    152c:	48 89 c6             	mov    %rax,%rsi
    152f:	48 8d 05 82 0b 00 00 	lea    0xb82(%rip),%rax        # 20b8 <_IO_stdin_used+0xb8>
    1536:	48 89 c7             	mov    %rax,%rdi
    1539:	b8 00 00 00 00       	mov    $0x0,%eax
    153e:	e8 bd fb ff ff       	call   1100 <printf@plt>
    1543:	48 83 45 d8 08       	addq   $0x8,-0x28(%rbp)
    1548:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    154c:	48 8b 00             	mov    (%rax),%rax
    154f:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1553:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
    1558:	0f 85 97 fe ff ff    	jne    13f5 <tnt_app_main_cmd+0x6e>
    155e:	eb 27                	jmp    1587 <tnt_app_main_cmd+0x200>
    1560:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1564:	48 8d 15 26 0b 00 00 	lea    0xb26(%rip),%rdx        # 2091 <_IO_stdin_used+0x91>
    156b:	48 89 d6             	mov    %rdx,%rsi
    156e:	48 89 c7             	mov    %rax,%rdi
    1571:	e8 aa fb ff ff       	call   1120 <strcmp@plt>
    1576:	85 c0                	test   %eax,%eax
    1578:	75 0d                	jne    1587 <tnt_app_main_cmd+0x200>
    157a:	48 8d 05 15 0b 00 00 	lea    0xb15(%rip),%rax        # 2096 <_IO_stdin_used+0x96>
    1581:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    1585:	eb 2c                	jmp    15b3 <tnt_app_main_cmd+0x22c>
    1587:	48 83 45 d8 08       	addq   $0x8,-0x28(%rbp)
    158c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1590:	48 8b 00             	mov    (%rax),%rax
    1593:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1597:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
    159c:	75 c2                	jne    1560 <tnt_app_main_cmd+0x1d9>
    159e:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
    15a3:	75 0d                	jne    15b2 <tnt_app_main_cmd+0x22b>
    15a5:	48 8d 05 ea 0a 00 00 	lea    0xaea(%rip),%rax        # 2096 <_IO_stdin_used+0x96>
    15ac:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    15b0:	eb 01                	jmp    15b3 <tnt_app_main_cmd+0x22c>
    15b2:	90                   	nop
    15b3:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    15b7:	48 89 c6             	mov    %rax,%rsi
    15ba:	48 8d 05 13 0b 00 00 	lea    0xb13(%rip),%rax        # 20d4 <_IO_stdin_used+0xd4>
    15c1:	48 89 c7             	mov    %rax,%rdi
    15c4:	b8 00 00 00 00       	mov    $0x0,%eax
    15c9:	e8 32 fb ff ff       	call   1100 <printf@plt>
    15ce:	b8 00 00 00 00       	mov    $0x0,%eax
    15d3:	c9                   	leave  
    15d4:	c3                   	ret    

Disassembly of section .fini:

00000000000015d8 <_fini>:
    15d8:	f3 0f 1e fa          	endbr64 
    15dc:	48 83 ec 08          	sub    $0x8,%rsp
    15e0:	48 83 c4 08          	add    $0x8,%rsp
    15e4:	c3                   	ret    

Disassembly of section .rodata:

0000000000002000 <_IO_stdin_used>:
    2000:	01 00                	add    %eax,(%rax)
    2002:	02 00                	add    (%rax),%al
    2004:	00 00                	add    %al,(%rax)
    2006:	00 00                	add    %al,(%rax)
    2008:	45 52                	rex.RB push %r10
    200a:	52                   	push   %rdx
    200b:	4f 52                	rex.WRXB push %r10
    200d:	3a 20                	cmp    (%rax),%ah
    200f:	25 73 0a 00 00       	and    $0xa73,%eax
    2014:	00 00                	add    %al,(%rax)
    2016:	00 00                	add    %al,(%rax)
    2018:	74 6e                	je     2088 <_IO_stdin_used+0x88>
    201a:	74 5f                	je     207b <_IO_stdin_used+0x7b>
    201c:	67 65 74 63          	addr32 gs je 2083 <_IO_stdin_used+0x83>
    2020:	77 64                	ja     2086 <_IO_stdin_used+0x86>
    2022:	2c 20                	sub    $0x20,%al
    2024:	63 77 64             	movsxd 0x64(%rdi),%esi
    2027:	3a 20                	cmp    (%rax),%ah
    2029:	43 61                	rex.XB (bad) 
    202b:	6e                   	outsb  %ds:(%rsi),(%dx)
    202c:	6e                   	outsb  %ds:(%rsi),(%dx)
    202d:	6f                   	outsl  %ds:(%rsi),(%dx)
    202e:	74 20                	je     2050 <_IO_stdin_used+0x50>
    2030:	61                   	(bad)  
    2031:	6c                   	insb   (%dx),%es:(%rdi)
    2032:	6c                   	insb   (%dx),%es:(%rdi)
    2033:	6f                   	outsl  %ds:(%rsi),(%dx)
    2034:	63 61 74             	movsxd 0x74(%rcx),%esp
    2037:	65 20 65 6e          	and    %ah,%gs:0x6e(%rbp)
    203b:	6f                   	outsl  %ds:(%rsi),(%dx)
    203c:	75 67                	jne    20a5 <_IO_stdin_used+0xa5>
    203e:	68 20 6d 65 6d       	push   $0x6d656d20
    2043:	6f                   	outsl  %ds:(%rsi),(%dx)
    2044:	72 79                	jb     20bf <_IO_stdin_used+0xbf>
    2046:	2e 00 74 6e 74       	cs add %dh,0x74(%rsi,%rbp,2)
    204b:	5f                   	pop    %rdi
    204c:	67 65 74 63          	addr32 gs je 20b3 <_IO_stdin_used+0xb3>
    2050:	77 64                	ja     20b6 <_IO_stdin_used+0xb6>
    2052:	2c 20                	sub    $0x20,%al
    2054:	67 65 74 63          	addr32 gs je 20bb <_IO_stdin_used+0xbb>
    2058:	77 64                	ja     20be <_IO_stdin_used+0xbe>
    205a:	00 43 75             	add    %al,0x75(%rbx)
    205d:	72 72                	jb     20d1 <_IO_stdin_used+0xd1>
    205f:	65 6e                	outsb  %gs:(%rsi),(%dx)
    2061:	74 20                	je     2083 <_IO_stdin_used+0x83>
    2063:	77 6f                	ja     20d4 <_IO_stdin_used+0xd4>
    2065:	72 6b                	jb     20d2 <_IO_stdin_used+0xd2>
    2067:	69 6e 67 20 64 69 72 	imul   $0x72696420,0x67(%rsi),%ebp
    206e:	3a 20                	cmp    (%rax),%ah
    2070:	25 73 0a 00 73       	and    $0x73000a73,%eax
    2075:	73 73                	jae    20ea <__GNU_EH_FRAME_HDR+0x6>
    2077:	20 25 6c 64 0a 00    	and    %ah,0xa646c(%rip)        # a84e9 <_end+0xa44b9>
    207d:	76 65                	jbe    20e4 <__GNU_EH_FRAME_HDR>
    207f:	72 73                	jb     20f4 <__GNU_EH_FRAME_HDR+0x10>
    2081:	69 6f 6e 00 43 4d 44 	imul   $0x444d4300,0x6e(%rdi),%ebp
    2088:	5f                   	pop    %rdi
    2089:	56                   	push   %rsi
    208a:	45 52                	rex.RB push %r10
    208c:	53                   	push   %rbx
    208d:	49                   	rex.WB
    208e:	4f                   	rex.WRXB
    208f:	4e 00 68 65          	rex.WRX add %r13b,0x65(%rax)
    2093:	6c                   	insb   (%dx),%es:(%rdi)
    2094:	70 00                	jo     2096 <_IO_stdin_used+0x96>
    2096:	43                   	rex.XB
    2097:	4d                   	rex.WRB
    2098:	44 5f                	rex.R pop %rdi
    209a:	48                   	rex.W
    209b:	45                   	rex.RB
    209c:	4c 50                	rex.WR push %rax
    209e:	00 77 6f             	add    %dh,0x6f(%rdi)
    20a1:	72 6b                	jb     210e <__GNU_EH_FRAME_HDR+0x2a>
    20a3:	69 6e 67 2d 64 69 72 	imul   $0x7269642d,0x67(%rsi),%ebp
    20aa:	65 63 74 6f 72       	movsxd %gs:0x72(%rdi,%rbp,2),%esi
    20af:	79 3d                	jns    20ee <__GNU_EH_FRAME_HDR+0xa>
    20b1:	00 76 00             	add    %dh,0x0(%rsi)
    20b4:	68 00 64 00 40       	push   $0x40006400
    20b9:	53                   	push   %rbx
    20ba:	65 74 20             	gs je  20dd <_IO_stdin_used+0xdd>
    20bd:	77 6f                	ja     212e <__GNU_EH_FRAME_HDR+0x4a>
    20bf:	72 6b                	jb     212c <__GNU_EH_FRAME_HDR+0x48>
    20c1:	69 6e 67 20 64 69 72 	imul   $0x72696420,0x67(%rsi),%ebp
    20c8:	65 63 74 6f 72       	movsxd %gs:0x72(%rdi,%rbp,2),%esi
    20cd:	79 3a                	jns    2109 <__GNU_EH_FRAME_HDR+0x25>
    20cf:	20 25 73 0a 00 40    	and    %ah,0x40000a73(%rip)        # 40002b48 <_end+0x3fffeb18>
    20d5:	52                   	push   %rdx
    20d6:	75 6e                	jne    2146 <__GNU_EH_FRAME_HDR+0x62>
    20d8:	20 63 6d             	and    %ah,0x6d(%rbx)
    20db:	64                   	fs
    20dc:	20                   	.byte 0x20
    20dd:	25                   	.byte 0x25
    20de:	73 0a                	jae    20ea <__GNU_EH_FRAME_HDR+0x6>
	...

Disassembly of section .eh_frame_hdr:

00000000000020e4 <__GNU_EH_FRAME_HDR>:
    20e4:	01 1b                	add    %ebx,(%rbx)
    20e6:	03 3b                	add    (%rbx),%edi
    20e8:	48 00 00             	rex.W add %al,(%rax)
    20eb:	00 08                	add    %cl,(%rax)
    20ed:	00 00                	add    %al,(%rax)
    20ef:	00 3c ef             	add    %bh,(%rdi,%rbp,8)
    20f2:	ff                   	(bad)  
    20f3:	ff                   	(bad)  
    20f4:	7c 00                	jl     20f6 <__GNU_EH_FRAME_HDR+0x12>
    20f6:	00 00                	add    %al,(%rax)
    20f8:	ec                   	in     (%dx),%al
    20f9:	ef                   	out    %eax,(%dx)
    20fa:	ff                   	(bad)  
    20fb:	ff a4 00 00 00 fc ef 	jmp    *-0x10040000(%rax,%rax,1)
    2102:	ff                   	(bad)  
    2103:	ff                   	(bad)  
    2104:	bc 00 00 00 9c       	mov    $0x9c000000,%esp
    2109:	f0 ff                	lock (bad) 
    210b:	ff 64 00 00          	jmp    *0x0(%rax,%rax,1)
    210f:	00 85 f1 ff ff d4    	add    %al,-0x2b00000f(%rbp)
    2115:	00 00                	add    %al,(%rax)
    2117:	00 af f1 ff ff f4    	add    %ch,-0xb00000f(%rdi)
    211d:	00 00                	add    %al,(%rax)
    211f:	00 eb                	add    %ch,%bl
    2121:	f1                   	int1   
    2122:	ff                   	(bad)  
    2123:	ff 10                	call   *(%rax)
    2125:	01 00                	add    %eax,(%rax)
    2127:	00 a3 f2 ff ff 30    	add    %ah,0x30fffff2(%rbx)
    212d:	01 00                	add    %eax,(%rax)
	...

Disassembly of section .eh_frame:

0000000000002130 <__FRAME_END__-0x104>:
    2130:	14 00                	adc    $0x0,%al
    2132:	00 00                	add    %al,(%rax)
    2134:	00 00                	add    %al,(%rax)
    2136:	00 00                	add    %al,(%rax)
    2138:	01 7a 52             	add    %edi,0x52(%rdx)
    213b:	00 01                	add    %al,(%rcx)
    213d:	78 10                	js     214f <__GNU_EH_FRAME_HDR+0x6b>
    213f:	01 1b                	add    %ebx,(%rbx)
    2141:	0c 07                	or     $0x7,%al
    2143:	08 90 01 00 00 14    	or     %dl,0x14000001(%rax)
    2149:	00 00                	add    %al,(%rax)
    214b:	00 1c 00             	add    %bl,(%rax,%rax,1)
    214e:	00 00                	add    %al,(%rax)
    2150:	30 f0                	xor    %dh,%al
    2152:	ff                   	(bad)  
    2153:	ff 26                	jmp    *(%rsi)
    2155:	00 00                	add    %al,(%rax)
    2157:	00 00                	add    %al,(%rax)
    2159:	44 07                	rex.R (bad) 
    215b:	10 00                	adc    %al,(%rax)
    215d:	00 00                	add    %al,(%rax)
    215f:	00 24 00             	add    %ah,(%rax,%rax,1)
    2162:	00 00                	add    %al,(%rax)
    2164:	34 00                	xor    $0x0,%al
    2166:	00 00                	add    %al,(%rax)
    2168:	b8 ee ff ff b0       	mov    $0xb0ffffee,%eax
    216d:	00 00                	add    %al,(%rax)
    216f:	00 00                	add    %al,(%rax)
    2171:	0e                   	(bad)  
    2172:	10 46 0e             	adc    %al,0xe(%rsi)
    2175:	18 4a 0f             	sbb    %cl,0xf(%rdx)
    2178:	0b 77 08             	or     0x8(%rdi),%esi
    217b:	80 00 3f             	addb   $0x3f,(%rax)
    217e:	1a 3a                	sbb    (%rdx),%bh
    2180:	2a 33                	sub    (%rbx),%dh
    2182:	24 22                	and    $0x22,%al
    2184:	00 00                	add    %al,(%rax)
    2186:	00 00                	add    %al,(%rax)
    2188:	14 00                	adc    $0x0,%al
    218a:	00 00                	add    %al,(%rax)
    218c:	5c                   	pop    %rsp
    218d:	00 00                	add    %al,(%rax)
    218f:	00 40 ef             	add    %al,-0x11(%rax)
    2192:	ff                   	(bad)  
    2193:	ff 10                	call   *(%rax)
	...
    219d:	00 00                	add    %al,(%rax)
    219f:	00 14 00             	add    %dl,(%rax,%rax,1)
    21a2:	00 00                	add    %al,(%rax)
    21a4:	74 00                	je     21a6 <__GNU_EH_FRAME_HDR+0xc2>
    21a6:	00 00                	add    %al,(%rax)
    21a8:	38 ef                	cmp    %ch,%bh
    21aa:	ff                   	(bad)  
    21ab:	ff a0 00 00 00 00    	jmp    *0x0(%rax)
    21b1:	00 00                	add    %al,(%rax)
    21b3:	00 00                	add    %al,(%rax)
    21b5:	00 00                	add    %al,(%rax)
    21b7:	00 1c 00             	add    %bl,(%rax,%rax,1)
    21ba:	00 00                	add    %al,(%rax)
    21bc:	8c 00                	mov    %es,(%rax)
    21be:	00 00                	add    %al,(%rax)
    21c0:	a9 f0 ff ff 2a       	test   $0x2afffff0,%eax
    21c5:	00 00                	add    %al,(%rax)
    21c7:	00 00                	add    %al,(%rax)
    21c9:	45 0e                	rex.RB (bad) 
    21cb:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    21d1:	61                   	(bad)  
    21d2:	0c 07                	or     $0x7,%al
    21d4:	08 00                	or     %al,(%rax)
    21d6:	00 00                	add    %al,(%rax)
    21d8:	18 00                	sbb    %al,(%rax)
    21da:	00 00                	add    %al,(%rax)
    21dc:	ac                   	lods   %ds:(%rsi),%al
    21dd:	00 00                	add    %al,(%rax)
    21df:	00 b3 f0 ff ff 3c    	add    %dh,0x3cfffff0(%rbx)
    21e5:	00 00                	add    %al,(%rax)
    21e7:	00 00                	add    %al,(%rax)
    21e9:	45 0e                	rex.RB (bad) 
    21eb:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    21f1:	00 00                	add    %al,(%rax)
    21f3:	00 1c 00             	add    %bl,(%rax,%rax,1)
    21f6:	00 00                	add    %al,(%rax)
    21f8:	c8 00 00 00          	enter  $0x0,$0x0
    21fc:	d3 f0                	shl    %cl,%eax
    21fe:	ff                   	(bad)  
    21ff:	ff                   	(bad)  
    2200:	b8 00 00 00 00       	mov    $0x0,%eax
    2205:	45 0e                	rex.RB (bad) 
    2207:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    220d:	02 af 0c 07 08 00    	add    0x8070c(%rdi),%ch
    2213:	00 1c 00             	add    %bl,(%rax,%rax,1)
    2216:	00 00                	add    %al,(%rax)
    2218:	e8 00 00 00 6b       	call   6b00221d <_end+0x6affe1ed>
    221d:	f1                   	int1   
    221e:	ff                   	(bad)  
    221f:	ff 4e 02             	decl   0x2(%rsi)
    2222:	00 00                	add    %al,(%rax)
    2224:	00 45 0e             	add    %al,0xe(%rbp)
    2227:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    222d:	03 45 02             	add    0x2(%rbp),%eax
    2230:	0c 07                	or     $0x7,%al
    2232:	08 00                	or     %al,(%rax)

0000000000002234 <__FRAME_END__>:
    2234:	00 00                	add    %al,(%rax)
	...

Disassembly of section .init_array:

0000000000003d70 <__frame_dummy_init_array_entry>:
    3d70:	60                   	(bad)  
    3d71:	12 00                	adc    (%rax),%al
    3d73:	00 00                	add    %al,(%rax)
    3d75:	00 00                	add    %al,(%rax)
	...

Disassembly of section .fini_array:

0000000000003d78 <__do_global_dtors_aux_fini_array_entry>:
    3d78:	20 12                	and    %dl,(%rdx)
    3d7a:	00 00                	add    %al,(%rax)
    3d7c:	00 00                	add    %al,(%rax)
	...

Disassembly of section .dynamic:

0000000000003d80 <_DYNAMIC>:
    3d80:	01 00                	add    %eax,(%rax)
    3d82:	00 00                	add    %al,(%rax)
    3d84:	00 00                	add    %al,(%rax)
    3d86:	00 00                	add    %al,(%rax)
    3d88:	75 00                	jne    3d8a <_DYNAMIC+0xa>
    3d8a:	00 00                	add    %al,(%rax)
    3d8c:	00 00                	add    %al,(%rax)
    3d8e:	00 00                	add    %al,(%rax)
    3d90:	0c 00                	or     $0x0,%al
    3d92:	00 00                	add    %al,(%rax)
    3d94:	00 00                	add    %al,(%rax)
    3d96:	00 00                	add    %al,(%rax)
    3d98:	00 10                	add    %dl,(%rax)
    3d9a:	00 00                	add    %al,(%rax)
    3d9c:	00 00                	add    %al,(%rax)
    3d9e:	00 00                	add    %al,(%rax)
    3da0:	0d 00 00 00 00       	or     $0x0,%eax
    3da5:	00 00                	add    %al,(%rax)
    3da7:	00 d8                	add    %bl,%al
    3da9:	15 00 00 00 00       	adc    $0x0,%eax
    3dae:	00 00                	add    %al,(%rax)
    3db0:	19 00                	sbb    %eax,(%rax)
    3db2:	00 00                	add    %al,(%rax)
    3db4:	00 00                	add    %al,(%rax)
    3db6:	00 00                	add    %al,(%rax)
    3db8:	70 3d                	jo     3df7 <_DYNAMIC+0x77>
    3dba:	00 00                	add    %al,(%rax)
    3dbc:	00 00                	add    %al,(%rax)
    3dbe:	00 00                	add    %al,(%rax)
    3dc0:	1b 00                	sbb    (%rax),%eax
    3dc2:	00 00                	add    %al,(%rax)
    3dc4:	00 00                	add    %al,(%rax)
    3dc6:	00 00                	add    %al,(%rax)
    3dc8:	08 00                	or     %al,(%rax)
    3dca:	00 00                	add    %al,(%rax)
    3dcc:	00 00                	add    %al,(%rax)
    3dce:	00 00                	add    %al,(%rax)
    3dd0:	1a 00                	sbb    (%rax),%al
    3dd2:	00 00                	add    %al,(%rax)
    3dd4:	00 00                	add    %al,(%rax)
    3dd6:	00 00                	add    %al,(%rax)
    3dd8:	78 3d                	js     3e17 <_DYNAMIC+0x97>
    3dda:	00 00                	add    %al,(%rax)
    3ddc:	00 00                	add    %al,(%rax)
    3dde:	00 00                	add    %al,(%rax)
    3de0:	1c 00                	sbb    $0x0,%al
    3de2:	00 00                	add    %al,(%rax)
    3de4:	00 00                	add    %al,(%rax)
    3de6:	00 00                	add    %al,(%rax)
    3de8:	08 00                	or     %al,(%rax)
    3dea:	00 00                	add    %al,(%rax)
    3dec:	00 00                	add    %al,(%rax)
    3dee:	00 00                	add    %al,(%rax)
    3df0:	f5                   	cmc    
    3df1:	fe                   	(bad)  
    3df2:	ff 6f 00             	ljmp   *0x0(%rdi)
    3df5:	00 00                	add    %al,(%rax)
    3df7:	00 b0 03 00 00 00    	add    %dh,0x3(%rax)
    3dfd:	00 00                	add    %al,(%rax)
    3dff:	00 05 00 00 00 00    	add    %al,0x0(%rip)        # 3e05 <_DYNAMIC+0x85>
    3e05:	00 00                	add    %al,(%rax)
    3e07:	00 70 05             	add    %dh,0x5(%rax)
    3e0a:	00 00                	add    %al,(%rax)
    3e0c:	00 00                	add    %al,(%rax)
    3e0e:	00 00                	add    %al,(%rax)
    3e10:	06                   	(bad)  
    3e11:	00 00                	add    %al,(%rax)
    3e13:	00 00                	add    %al,(%rax)
    3e15:	00 00                	add    %al,(%rax)
    3e17:	00 d8                	add    %bl,%al
    3e19:	03 00                	add    (%rax),%eax
    3e1b:	00 00                	add    %al,(%rax)
    3e1d:	00 00                	add    %al,(%rax)
    3e1f:	00 0a                	add    %cl,(%rdx)
    3e21:	00 00                	add    %al,(%rax)
    3e23:	00 00                	add    %al,(%rax)
    3e25:	00 00                	add    %al,(%rax)
    3e27:	00 db                	add    %bl,%bl
    3e29:	00 00                	add    %al,(%rax)
    3e2b:	00 00                	add    %al,(%rax)
    3e2d:	00 00                	add    %al,(%rax)
    3e2f:	00 0b                	add    %cl,(%rbx)
    3e31:	00 00                	add    %al,(%rax)
    3e33:	00 00                	add    %al,(%rax)
    3e35:	00 00                	add    %al,(%rax)
    3e37:	00 18                	add    %bl,(%rax)
    3e39:	00 00                	add    %al,(%rax)
    3e3b:	00 00                	add    %al,(%rax)
    3e3d:	00 00                	add    %al,(%rax)
    3e3f:	00 15 00 00 00 00    	add    %dl,0x0(%rip)        # 3e45 <_DYNAMIC+0xc5>
	...
    3e4d:	00 00                	add    %al,(%rax)
    3e4f:	00 03                	add    %al,(%rbx)
    3e51:	00 00                	add    %al,(%rax)
    3e53:	00 00                	add    %al,(%rax)
    3e55:	00 00                	add    %al,(%rax)
    3e57:	00 70 3f             	add    %dh,0x3f(%rax)
    3e5a:	00 00                	add    %al,(%rax)
    3e5c:	00 00                	add    %al,(%rax)
    3e5e:	00 00                	add    %al,(%rax)
    3e60:	02 00                	add    (%rax),%al
    3e62:	00 00                	add    %al,(%rax)
    3e64:	00 00                	add    %al,(%rax)
    3e66:	00 00                	add    %al,(%rax)
    3e68:	f0 00 00             	lock add %al,(%rax)
    3e6b:	00 00                	add    %al,(%rax)
    3e6d:	00 00                	add    %al,(%rax)
    3e6f:	00 14 00             	add    %dl,(%rax,%rax,1)
    3e72:	00 00                	add    %al,(%rax)
    3e74:	00 00                	add    %al,(%rax)
    3e76:	00 00                	add    %al,(%rax)
    3e78:	07                   	(bad)  
    3e79:	00 00                	add    %al,(%rax)
    3e7b:	00 00                	add    %al,(%rax)
    3e7d:	00 00                	add    %al,(%rax)
    3e7f:	00 17                	add    %dl,(%rdi)
    3e81:	00 00                	add    %al,(%rax)
    3e83:	00 00                	add    %al,(%rax)
    3e85:	00 00                	add    %al,(%rax)
    3e87:	00 78 07             	add    %bh,0x7(%rax)
    3e8a:	00 00                	add    %al,(%rax)
    3e8c:	00 00                	add    %al,(%rax)
    3e8e:	00 00                	add    %al,(%rax)
    3e90:	07                   	(bad)  
    3e91:	00 00                	add    %al,(%rax)
    3e93:	00 00                	add    %al,(%rax)
    3e95:	00 00                	add    %al,(%rax)
    3e97:	00 a0 06 00 00 00    	add    %ah,0x6(%rax)
    3e9d:	00 00                	add    %al,(%rax)
    3e9f:	00 08                	add    %cl,(%rax)
    3ea1:	00 00                	add    %al,(%rax)
    3ea3:	00 00                	add    %al,(%rax)
    3ea5:	00 00                	add    %al,(%rax)
    3ea7:	00 d8                	add    %bl,%al
    3ea9:	00 00                	add    %al,(%rax)
    3eab:	00 00                	add    %al,(%rax)
    3ead:	00 00                	add    %al,(%rax)
    3eaf:	00 09                	add    %cl,(%rcx)
    3eb1:	00 00                	add    %al,(%rax)
    3eb3:	00 00                	add    %al,(%rax)
    3eb5:	00 00                	add    %al,(%rax)
    3eb7:	00 18                	add    %bl,(%rax)
    3eb9:	00 00                	add    %al,(%rax)
    3ebb:	00 00                	add    %al,(%rax)
    3ebd:	00 00                	add    %al,(%rax)
    3ebf:	00 1e                	add    %bl,(%rsi)
    3ec1:	00 00                	add    %al,(%rax)
    3ec3:	00 00                	add    %al,(%rax)
    3ec5:	00 00                	add    %al,(%rax)
    3ec7:	00 08                	add    %cl,(%rax)
    3ec9:	00 00                	add    %al,(%rax)
    3ecb:	00 00                	add    %al,(%rax)
    3ecd:	00 00                	add    %al,(%rax)
    3ecf:	00 fb                	add    %bh,%bl
    3ed1:	ff                   	(bad)  
    3ed2:	ff 6f 00             	ljmp   *0x0(%rdi)
    3ed5:	00 00                	add    %al,(%rax)
    3ed7:	00 01                	add    %al,(%rcx)
    3ed9:	00 00                	add    %al,(%rax)
    3edb:	08 00                	or     %al,(%rax)
    3edd:	00 00                	add    %al,(%rax)
    3edf:	00 fe                	add    %bh,%dh
    3ee1:	ff                   	(bad)  
    3ee2:	ff 6f 00             	ljmp   *0x0(%rdi)
    3ee5:	00 00                	add    %al,(%rax)
    3ee7:	00 70 06             	add    %dh,0x6(%rax)
    3eea:	00 00                	add    %al,(%rax)
    3eec:	00 00                	add    %al,(%rax)
    3eee:	00 00                	add    %al,(%rax)
    3ef0:	ff                   	(bad)  
    3ef1:	ff                   	(bad)  
    3ef2:	ff 6f 00             	ljmp   *0x0(%rdi)
    3ef5:	00 00                	add    %al,(%rax)
    3ef7:	00 01                	add    %al,(%rcx)
    3ef9:	00 00                	add    %al,(%rax)
    3efb:	00 00                	add    %al,(%rax)
    3efd:	00 00                	add    %al,(%rax)
    3eff:	00 f0                	add    %dh,%al
    3f01:	ff                   	(bad)  
    3f02:	ff 6f 00             	ljmp   *0x0(%rdi)
    3f05:	00 00                	add    %al,(%rax)
    3f07:	00 4c 06 00          	add    %cl,0x0(%rsi,%rax,1)
    3f0b:	00 00                	add    %al,(%rax)
    3f0d:	00 00                	add    %al,(%rax)
    3f0f:	00 f9                	add    %bh,%cl
    3f11:	ff                   	(bad)  
    3f12:	ff 6f 00             	ljmp   *0x0(%rdi)
    3f15:	00 00                	add    %al,(%rax)
    3f17:	00 03                	add    %al,(%rbx)
	...

Disassembly of section .got:

0000000000003f70 <_GLOBAL_OFFSET_TABLE_>:
    3f70:	80 3d 00 00 00 00 00 	cmpb   $0x0,0x0(%rip)        # 3f77 <_GLOBAL_OFFSET_TABLE_+0x7>
	...
    3f87:	00 30                	add    %dh,(%rax)
    3f89:	10 00                	adc    %al,(%rax)
    3f8b:	00 00                	add    %al,(%rax)
    3f8d:	00 00                	add    %al,(%rax)
    3f8f:	00 40 10             	add    %al,0x10(%rax)
    3f92:	00 00                	add    %al,(%rax)
    3f94:	00 00                	add    %al,(%rax)
    3f96:	00 00                	add    %al,(%rax)
    3f98:	50                   	push   %rax
    3f99:	10 00                	adc    %al,(%rax)
    3f9b:	00 00                	add    %al,(%rax)
    3f9d:	00 00                	add    %al,(%rax)
    3f9f:	00 60 10             	add    %ah,0x10(%rax)
    3fa2:	00 00                	add    %al,(%rax)
    3fa4:	00 00                	add    %al,(%rax)
    3fa6:	00 00                	add    %al,(%rax)
    3fa8:	70 10                	jo     3fba <_GLOBAL_OFFSET_TABLE_+0x4a>
    3faa:	00 00                	add    %al,(%rax)
    3fac:	00 00                	add    %al,(%rax)
    3fae:	00 00                	add    %al,(%rax)
    3fb0:	80 10 00             	adcb   $0x0,(%rax)
    3fb3:	00 00                	add    %al,(%rax)
    3fb5:	00 00                	add    %al,(%rax)
    3fb7:	00 90 10 00 00 00    	add    %dl,0x10(%rax)
    3fbd:	00 00                	add    %al,(%rax)
    3fbf:	00 a0 10 00 00 00    	add    %ah,0x10(%rax)
    3fc5:	00 00                	add    %al,(%rax)
    3fc7:	00 b0 10 00 00 00    	add    %dh,0x10(%rax)
    3fcd:	00 00                	add    %al,(%rax)
    3fcf:	00 c0                	add    %al,%al
    3fd1:	10 00                	adc    %al,(%rax)
	...

Disassembly of section .data:

0000000000004000 <__data_start>:
	...

0000000000004008 <__dso_handle>:
    4008:	08 40 00             	or     %al,0x0(%rax)
    400b:	00 00                	add    %al,(%rax)
    400d:	00 00                	add    %al,(%rax)
	...

Disassembly of section .bss:

0000000000004020 <stderr@GLIBC_2.2.5>:
	...

0000000000004028 <completed.0>:
	...

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	47                   	rex.RXB
   1:	43                   	rex.XB
   2:	43 3a 20             	rex.XB cmp (%r8),%spl
   5:	28 55 62             	sub    %dl,0x62(%rbp)
   8:	75 6e                	jne    78 <__abi_tag-0x314>
   a:	74 75                	je     81 <__abi_tag-0x30b>
   c:	20 31                	and    %dh,(%rcx)
   e:	31 2e                	xor    %ebp,(%rsi)
  10:	34 2e                	xor    $0x2e,%al
  12:	30 2d 31 75 62 75    	xor    %ch,0x75627531(%rip)        # 75627549 <_end+0x75623519>
  18:	6e                   	outsb  %ds:(%rsi),(%dx)
  19:	74 75                	je     90 <__abi_tag-0x2fc>
  1b:	31 7e 32             	xor    %edi,0x32(%rsi)
  1e:	32 2e                	xor    (%rsi),%ch
  20:	30 34 29             	xor    %dh,(%rcx,%rbp,1)
  23:	20 31                	and    %dh,(%rcx)
  25:	31 2e                	xor    %ebp,(%rsi)
  27:	34 2e                	xor    $0x2e,%al
  29:	30 00                	xor    %al,(%rax)
