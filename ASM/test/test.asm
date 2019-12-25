assume CS:code DS:data SS:stack
data segment
    
    dw 8F61H,8F72H,8F79H,8F61H,8F6EH,8F20H,8F6CH,8F6FH,8F76H,8F65H,8F20H,8F61H,8F72H,8F79H,8F61H
    
data ends

stack segment
    
    dw 0,0,0,0,0
    
stack ends

code segment

start:
    mov AX,0B800H
    mov SS,AX
    
    mov AX,data
    mov DS,AX

    mov BX,0
    mov BP,0
    mov CX,15
s:  
    mov AX,[BX]
    mov [BP],AX
    add BX,2
    add BP,2
    loop s
    call s
    call far ptr s
    call AX
    call dword ptr DS:[0]
    shl AX,2
    shr AX,2
    
    
code ends

end start