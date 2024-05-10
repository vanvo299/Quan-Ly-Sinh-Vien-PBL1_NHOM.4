#ifndef STUDENT_H
#define STUDENT_H

struct SinhVien {
    char ten[100];
    char maSV[20];
    char email[30];
    char lop[100];
    double gpa;
    double canNang;
    char gioiTinh[5];
    double chieuCao;
    double BMI;
    char diaChi[30];
    char DOB[30];
};

typedef struct SinhVien SinhVien;

void in(SinhVien *x, int n);
void toLowerCase(char str[]);
void timKiemTheoTen(SinhVien a[], int n, char name[]);

int soSanhMaSV(const void *a, const void *b);
void timKiemTheoMaSV(SinhVien a[], int n, char ID[]);

void xoaThongTin(SinhVien a[], int* n, char ID[]);

#endif