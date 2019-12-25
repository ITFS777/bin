assume CS:code DS:data SS:stack
data segment
    
    dw 756FH,5920H,6576H,6F4CH,2049H
    
data ends

stack segment
    
    dw 0,0,0,0,0
    
stack ends

code segment

start:
    mov AX,stack
    mov SS,AX
    mov AX,0
    
    mov AX,data
    mov DS,AX
    mov AX,0
        
    mov AX,000AH
    mov SP,AX
    mov AX,0

    mov CX,5H
    mov BX,0    
in: 
    push DS:[BX]
    add BX,2
    loop in
    
code ends

end start