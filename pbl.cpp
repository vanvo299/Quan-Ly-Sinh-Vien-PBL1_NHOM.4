/*
DỰ ÁN PBL1: LẬP TRÌNH TÍNH TOÁN
Chủ đề: Xây dựng chương trình quản lý sinh viên
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct SinhVien {
    char ten[100];
    char maSV[20];
    char lop[100];
    double gpa;
    double canNang;
    char gioiTinh[5];
    double chieuCao;
    double BMI;
};

typedef struct SinhVien SinhVien;

// Nhap thong tin sinh vien va tra ve sinh vien sau khi nhap
void Nhap(SinhVien* x)
{
    getchar();
    printf("Nhap ten: "); gets(x->ten);
    printf("Nhap ma sinh vien: "); gets(x->maSV);
    printf("Nhap gioi tinh: "); gets(x->gioiTinh);
    printf("Nhap lop: "); gets(x->lop);
    printf("Nhap gpa: "); scanf("%lf", &x->gpa);
    printf("Nhap can nang: "); scanf("%lf", &x->canNang);
    printf("Nhap chieu cao: "); scanf("%lf", &x->chieuCao);
    printf("\n");
}
void tinh_BMI(SinhVien *x) { 
    double chieuCao_meters = x->chieuCao / 100.0;
    x->BMI = x->canNang / pow(chieuCao_meters, 2);
}
void in(SinhVien *x)
{
    printf("Ho va ten: %s\n", x->ten);
    printf("Ma sinh vien: %s\n", x->maSV); 
    printf("Gioi tinh: %s\n", x->gioiTinh);
    printf("Lop: %s\n", x->lop);
    printf("GPA: %.2lf\n", x->gpa);
    printf("Can nang: %.1lf\n", x->canNang);
    printf("Chieu cao: %.1lf\n", x->chieuCao);
    tinh_BMI(x);
    printf("BMI: %.2lf\n\n", x->BMI);
}

void xuatFile(SinhVien *x, int n) {
    FILE *outputFile = fopen("danhSachSinhVien.txt", "w");
    
    if (outputFile) {
        for (int i = 0; i < n; i++) {
            fprintf(outputFile, "Sinh vien %d:\n", i + 1);
            fprintf(outputFile, "Ho va ten: %s\n", x[i].ten);
            fprintf(outputFile, "Ma sinh vien: %s\n", x[i].maSV);
            fprintf(outputFile, "Gioi tinh: %s\n", x[i].gioiTinh);
            fprintf(outputFile, "Lop: %s\n", x[i].lop);
            fprintf(outputFile, "GPA: %.2lf\n", x[i].gpa);
            fprintf(outputFile, "Can nang: %.1lf\n", x[i].canNang);
            fprintf(outputFile, "Chieu cao: %.1lf cm\n", x[i].chieuCao);
            tinh_BMI(&x[i]);
            fprintf(outputFile, "BMI: %.2lf\n\n", x[i].BMI);
        }
        fclose(outputFile); 
    } else {
        printf("Error opening file for writing.\n");
    }
}

void timkiem(SinhVien a[], int n, char name[])
{
    int find = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(name, a[i].ten) == 0) {
            in(&a[i]);
            find = 1;
        }
    }
    if (find == 0) {
        printf("Khong tim thay sinh vien\n");
    }
}

// In ra nhung sinh vien co diem gpa cao nhat
void maxgpa(SinhVien a[], int n)
{
    double max = 0;
    for (int i = 0; i < n; i++) {
        max = fmax(max, a[i].gpa);
    }
    printf("Thong tin cac sinh vien co diem gpa cao nhat: \n");
    for (int i = 0; i < n; i++) {
        if (max == a[i].gpa) {
            in(&a[i]);
        }
    }
}
// xoa sinh vien theo ten
void xoaThongTin(SinhVien a[], int* n, char name[]) {
    for (int i = 0; i < *n; i++) {
        if (strcmp(a[i].ten, name) == 0) {
            for (int j = i; j < *n - 1; j++) {
                a[j] = a[j + 1];
            }
            (*n)--;
            break;
        }
    }
}

//Sap xep sinh vien theo gpa giam dan
void sapxep(SinhVien a[], int n)
{
    for (int i = 0; i < n; i++) {
        int max = i;
        for (int j = i + 1; j < n; j++) {
            if (a[max].gpa < a[j].gpa)
                max = j;
        }
        SinhVien temp = a[max];
        a[max] = a[i];
        a[i] = temp;
    }
}
// Sap xep quicksort
int cmp(const void* a, const void* b)
{
    SinhVien* x = (SinhVien*)a;
    SinhVien* y = (SinhVien*)b;
    return y->gpa - x->gpa;
}
int main()
{
    SinhVien a[1000];
    int n;
    while (1) {
        printf("-------------------QUAN LY SINH VIEN-------------------\n\n");
        printf("1. Nhap danh sach sinh vien\n");
        printf("2. Xuat file danh sach sinh vien\n");
        printf("3. Tim kiem sinh vien theo ten\n");
        printf("4. Liet ke sinh vien co diem cao nhat\n");
        printf("5. Xoa sinh vien theo ten\n");
        printf("6. Sap xep sinh vien theo gpa giam dan\n");
        printf("7. Hien thi danh sach sinh vien\n");
        printf("0. Thoat !\n");
        printf("-------------------------------------------------------\n\n");
        printf("Nhap lua chon: ");
        int lc; scanf("%d", &lc);
        if (lc == 1) {
            printf("Nhap so luong sinh vien: "); scanf("%d", &n);
            for (int i = 0; i < n; i++) {
            	printf("Sinh vien %d : \n", i + 1);
                Nhap(&a[i]);
            }
        }
        else if (lc == 2) {
          xuatFile(a, n); 
        }
        else if (lc == 3) {
            char name[100];
            printf("Nhap ten sinh vien can tim kiem: ");
            getchar();
            gets(name);
            timkiem(a, n, name);
        }
        else if (lc == 4) {
            maxgpa(a, n);
        }
        else if (lc == 5) {
            char name[100];
            printf("Nhap ten danh sach sinh vien can xoa: "); 
            getchar();
            gets(name);
            xoaThongTin(a, &n, name);
        }
        else if (lc == 6) {
           sapxep(a, n);
//           qsort(a, n, sizeof(SinhVien), cmp);
        }
        else if (lc == 7) {
            printf("Danh sach sinh vien\n");
            for (int i = 0; i < n; i++) {
                in(&a[i]);
            }
        }
        else if (lc == 0) {
            break;
        }
    }
    return 0;
}