#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>


#include "sapXepThongTin_h.h"

void tachHoTen(char hoTen[], char ten[]) {
    // Tìm vị trí khoảng trắng cuối cùng trong họ tên
    char *viTriKhoangTrangCuoi = strrchr(hoTen, ' ');
    if (viTriKhoangTrangCuoi != NULL) {
        strcpy(ten, viTriKhoangTrangCuoi + 1);
    } else {
        strcpy(ten, hoTen);
    }
}

// Hàm so sánh tên của hai sinh viên
int soSanhTenSinhVien(SinhVien *sv1, SinhVien *sv2) {
    char tenSV1[100], tenSV2[100];
    tachHoTen(sv1->ten, tenSV1);
    tachHoTen(sv2->ten, tenSV2);
    return strcasecmp(tenSV1, tenSV2);
}

// Hàm đổi chỗ giữa hai sinh viên
void swapSinhVien(SinhVien *a, SinhVien *b) {
    struct SinhVien temp = *a;
    *a = *b;
    *b = temp;
}

// Hàm chia mảng theo pivot
int Pivot(SinhVien a[], int low, int high) {
    SinhVien pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (soSanhTenSinhVien(&a[j], &pivot) <= 0) {
            i++;
            swapSinhVien(&a[i], &a[j]);
        }
    }

    swapSinhVien(&a[i + 1], &a[high]);
    return i + 1;
}

// Hàm sắp xếp Quick Sort
void quickSort(SinhVien a[], int low, int high) {
    if (low < high) {
        int pivot = Pivot(a, low, high);

        quickSort(a, low, pivot - 1);
        quickSort(a, pivot + 1, high);
    }
}

// Hàm sắp xếp sinh viên theo tên bằng Quick Sort
void sapXepTheoTen(SinhVien a[], int n) {
    quickSort(a, 0, n - 1);
}

int soSanhGPA(struct SinhVien *sv1, struct SinhVien *sv2) {
    if (sv1->gpa > sv2->gpa)
        return 1; // sv1 có GPA cao hơn sv2
    else if (sv1->gpa < sv2->gpa)
        return -1; // sv1 có GPA thấp hơn sv2
    else
        return 0; // sv1 và sv2 có cùng GPA
}

// Hàm chia mảng theo pivot dựa trên GPA
int chiaMangTheoPivot(SinhVien a[], int low, int high) {
    SinhVien pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (soSanhGPA(&a[j], &pivot) > 0) {
            i++;
            swapSinhVien(&a[i], &a[j]);
        }
    }

    swapSinhVien(&a[i + 1], &a[high]);
    return i + 1;
}

// Hàm sắp xếp Quick Sort theo GPA
void sapXepTheoDiemGPA(SinhVien a[], int low, int high) {
    if (low < high) {
        int pivot = chiaMangTheoPivot(a, low, high);

        sapXepTheoDiemGPA(a, low, pivot - 1);
        sapXepTheoDiemGPA(a, pivot + 1, high);
    }
}

// Hàm sắp xếp sinh viên theo GPA từ cao xuống thấp bằng Quick Sort
void sapXepTheoGPA(SinhVien a[], int n) {
    sapXepTheoDiemGPA(a, 0, n - 1);
    printf("Danh sach sinh vien da duoc sap xep theo GPA tu cao xuong thap. \n");
}
