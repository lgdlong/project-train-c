#include <stdio.h>
#include <stdbool.h>


void lua_chon(int *choice) {
    printf("Moi nhap lua chon: ");
    scanf("%d", choice);
    printf("\n");
}

void ds_1(){
    printf("\n--LUA CHON DOI TUONG LAM VIEC--\n");
    printf("1. San pham\n");
    printf("2. Gio hang\n");
    printf("3. Don mua\n");
    printf("4. Thoat\n");
    printf("\n");
}

void work_with_san_pham() {
    int choice1;
    printf("1. Them san pham\n");
    printf("2. Xoa san pham\n");
    printf("3. Sua san pham\n");
    printf("\n");
    
    lua_chon(&choice1);

    switch (choice1) {
        case 1:
            printf("Nhap so luong san pham can them: ");
            int productQuantity;
            scanf("%d", &productQuantity);

            for (int i = 0; i < productQuantity; i++) {
                printf("SAN PHAM %d\n", i+1);
                
                printf("Nhap ten san pham\n");
                printf("Nhap so luong san pham: \n");
                printf("Nhap gia san pham: \n");
                printf("\n");
            }

            break;
            /*
            Gán số thứ tự cho sản phẩm ngay tại thời điểm nhập vào một sản phẩm có kiểu product
            */
        case 2:
            printf("Lua chon so thu tu cua san pham can xoa: \n");
            printf("\n");

            break;
            /*
            Mỗi sản phẩm sẽ được gán một số thứ tự theo thời điểm nhập vào từ 1 -> productQuantity
            Khi xóa sản phẩm sẽ lựa chọn số thứ tự để xóa theo số thứ tự
            */
        case 3:
            printf("Lua chon so thu tu cua san pham can sua: \n");
            printf("1. Sua ten san pham\n");
            printf("2. Sua so luong san pham\n");
            printf("3. Sua gia san pham\n");
            printf("\n");

            break;

        default:
            return;
    }
}

void work_with_gio_hang() {
    printf("1. In gio hang\n");
    printf("\n");
}
