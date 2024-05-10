#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>


#include "timKiemVaXoa_h.h"

// ham de chuyen xau tat ca thanh chu thuong (VD: HELLO -> hello)
void toLowerCase(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = tolower(str[i]); // Chuyển đổi ký tự thành chữ thường
        i++;
    }
}

void timKiemTheoTen(SinhVien a[], int n, char name[]) {
    int find = 0;
    for (int i = 0; i < n; i++) {
        char temp[200];
        strcpy(temp, a[i].ten);
        toLowerCase(temp);
        // Su dung strstr de kiem tra tên có xuat hien trong tên sinh viên không
        if (strstr(temp, name) != NULL) {
            if (!find) {
                printf("STT\tHO VA TEN\t        MA SINH VIEN\tEMAIL\t                        GIOI TINH\tLOP\t        GPA\tNGAY THANG NAM SINH \t DIA CHI\n");
            }
            printf("%d", i + 1);
            in(&a[i], n);
            find = 1;
        }
    }
    if (find == 0) {
        printf("Khong tim thay sinh vien co ten: %s\n", name);
    }
}

// tim kiem theo ma SV
int soSanhMaSV(const void *a, const void *b) {
    const SinhVien *svA = (const SinhVien *)a;
    const SinhVien *svB = (const SinhVien *)b;
    return strcmp(svA->maSV, svB->maSV);
}

// Hàm tìm kiếm theo mã sinh viên trong danh sách đã được sắp xếp
void timKiemTheoMaSV(SinhVien a[], int n, char ID[]) {
    // Sắp xếp danh sách sinh viên theo mã sinh viên để áp dụng tìm kiếm nhị phân
    qsort(a, n, sizeof(SinhVien), soSanhMaSV);

    int find = 0;
    
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        int cmp = strcmp(ID, a[mid].maSV);
        
        if (cmp == 0) {
            if (!find) {
                printf("STT\tHO VA TEN\t        MA SINH VIEN\tEMAIL\t                        GIOI TINH\tLOP\t        GPA\tNGAY THANG NAM SINH \t DIA CHI\n");
            }
            printf("%d", mid + 1);
            in(&a[mid], n); 
            find = 1; 
            break; 
        } else if (cmp < 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
    }
    }
    if (!find) {
        printf("Khong tim thay sinh vien co ma sinh vien: %s\n", ID);
    }
}

// xoa sinh vien theo ten (chi can ten)
void xoaThongTin(SinhVien a[], int* n, char ID[]) {
    int find = 0;
    for (int i = 0; i < *n; i++) {
        if (strcmp(a[i].maSV, ID) == 0) {
            for (int j = i; j < *n - 1; j++) {
                a[j] = a[j + 1];
            }
            (*n)--;
            find = 1;
            printf("Da xoa sinh vien co ma sinh vien: %s\n", ID);
            break;
        }
    }
    if (!find) {
        printf("Khong tim thay sinh vien co ma sinh vien: %s\n", ID);
    }
}

