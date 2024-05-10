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

void tachHoTen(char hoTen[], char ten[]);
int soSanhTenSinhVien(SinhVien *sv1, SinhVien *sv2);
void swapSinhVien(SinhVien *a, SinhVien *b);
int Pivot(SinhVien a[], int low, int high);
void quickSort(SinhVien a[], int low, int high);
void sapXepTheoTen(SinhVien a[], int n);

int soSanhGPA(struct SinhVien *sv1, struct SinhVien *sv2);
int chiaMangTheoPivot(SinhVien a[], int low, int high);
void sapXepTheoDiemGPA(SinhVien a[], int low, int high);
void sapXepTheoGPA(SinhVien a[], int n);




#endif