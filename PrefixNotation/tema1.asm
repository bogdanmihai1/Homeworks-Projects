%include "io.inc"

%define MAX_INPUT_SIZE 4096

section .bss
	expr: resb MAX_INPUT_SIZE         
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
	push ebp
	mov ebp, esp

	GET_STRING expr, MAX_INPUT_SIZE
	; your code goes here     
        ;golesc registrii
        xor eax, eax
        xor ebx, ebx
        xor ecx, ecx
        xor edx, edx
        mov edi, expr
        jmp create_num
        xor eax, eax
	pop ebp
	ret

create_num:
        ;parcurg sirul si transform stringul de cifre
        ;in numere 
        mov ecx, 10
        mov dl, [edi]
        inc edi
        ;verific daca urmeaza o operatie sau
        ;daca s-a terminat sirul
        cmp dl, " "
        je add_to_stack
        cmp dl, 43
        je adunare
        cmp dl, 45
        je minus
        cmp dl, 42
        je inmultire
        cmp dl, 47
        je impartire
        cmp dl, 0
        je afisare
        ;transform cifra din string in numar      
        sub dl, 48
        ;inmultesc numarul existent cu 10 si adaug
        ;ultima cifra
        push edx
        mul ecx
        pop edx
        add eax, edx
        ;repet pana ajung la un spatiu sau la
        ;caracterul null
        jmp create_num

create_num_neg:
        ;repet procesul de la create_num, dar inmultesc
        ;de fiecare data cu -10
        mov ecx, -10
        mov dl, [edi]
        inc edi
        cmp dl, " "
        je add_to_stack
        cmp dl, 43
        je adunare
        cmp dl, 45
        je minus
        cmp dl, 42
        je inmultire
        cmp dl, 47
        je impartire
        cmp dl, 0
        je afisare
        sub dl, 48
        push edx
        imul ecx
        pop edx
        add eax, edx
        ;din cauza inmultirii repetate cu -10,
        ;numarul va fi pozitiv mereu cand va avea
        ;un numar par de cifre
        cmp eax, 0        
        jle create_num_neg
        ;cand numarul devine pozitiv se transforma
        ;in forma lui negativa
        push ecx
        xor ecx, ecx
        sub ecx, eax
        mov eax, ecx
        pop ecx
        jmp create_num_neg

minus:
        ;verific daca minusul face parte dintr-un
        ;numar sau nu
        xor eax, eax
        xor ebx, ebx
        mov al, [edi]
        cmp al, 0
        je scadere
        cmp al, " "
        je scadere
        ;daca dupa minus nu urmeaza un spatiu sau
        ;sfarsitul sirului, creez un numar negativ       
        xor eax, eax
        xor ebx, ebx
        xor ecx, ecx
        xor edx, edx
        jmp create_num_neg

adunare:
        xor eax, eax
        xor ebx, ebx
        inc edi
        ;adunarea
        pop eax
        pop ebx
        add eax, ebx
        push eax
        ;golesc registrii
        xor eax, eax
        xor ebx, ebx
        xor ecx, ecx
        xor edx, edx
        jmp create_num

scadere:
        xor eax, eax
        xor ebx, ebx
        inc edi
        ;scaderea
        pop ebx
        pop eax
        sub eax, ebx
        push eax
        ;golesc registrii
        xor eax, eax
        xor ebx, ebx
        xor ecx, ecx
        xor edx, edx
        jmp create_num

inmultire:
        xor eax, eax
        xor ebx, ebx
        inc edi
        ;inmultirea
        pop eax
        pop ebx
        imul ebx
        push eax
        ;golesc registrii
        xor eax, eax
        xor ebx, ebx
        xor ecx, ecx
        xor edx, edx
        jmp create_num

impartire:
        xor eax, eax
        xor ebx, ebx
        inc edi
        ;impartirea
        pop ebx
        pop eax
        cdq
        idiv ebx
        push eax
        ;golesc registrii
        xor eax, eax
        xor ebx, ebx
        xor ecx, ecx
        xor edx, edx
        jmp create_num

add_to_stack:
        ;cand se formeaza un numar il adaug in
        ;stiva si golesc registrii
        push eax
        mov al, [edi]
        xor eax, eax
        xor ebx, ebx
        xor ecx, ecx
        xor edx, edx
        jmp create_num

afisare:
        pop eax
        ;verific daca rezultatul este negativ     
        cmp eax, 0
        jl afisare_neg
        ;afisare
        PRINT_UDEC 4, eax
        xor eax, eax
        pop ebp
        ret

afisare_neg:
        ;daca numarul este negativ, ii afisez
        ;valoarea in modul precedata de semnul "-"
        xor ecx, ecx
        sub ecx, eax
        mov eax, ecx
        PRINT_STRING "-"
        PRINT_UDEC 4, eax
        xor eax, eax
        pop ebp
        ret