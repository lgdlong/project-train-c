#include <stdio.h>
#include <stdbool.h>


void lua_chon(int *choose) {
    printf("Moi nhap lua chon: ");
    scanf("%d", choose);
}

void ds_1(){
    printf("1. San pham\n");
    // printf("1. ");
    printf("2. Don mua\n");
    printf("3. Mua hang\n");
    printf("4. Thoat\n");
}

void work_with_san_pham() {
    printf("1. Them san pham\n");
    printf("2. Xoa san pham\n");
    printf("3. Sua san pham\n");
}

void work_with_don_mua() {
    printf("1. In danh sach tat ca san pham\n");
    // printf("2. In danh sach tat ca san pham\n");
}

void work_with_gio_hang() {
    printf("1. In gio hang\n");
    // printf("1. In danh sach tat ca san pham\n");
}
