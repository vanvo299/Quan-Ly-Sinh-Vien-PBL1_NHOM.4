#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>


#include "nhapThongTin_h.h"

void Nhap(SinhVien* x, char* line) {
    char* token = strtok(line, "|");
    if (token != NULL)
        strcpy(x->ten, token);

    token = strtok(NULL, "|");
    if (token != NULL)
        strcpy(x->gioiTinh, token);

    token = strtok(NULL, "|");
    if (token != NULL)
        strcpy(x->lop, token);

    token = strtok(NULL, "|");
    if (token != NULL)
        x->gpa = atof(token);

    token = strtok(NULL, "|");
    if (token != NULL)
        strcpy(x->diaChi, token);

    token = strtok(NULL, "|");
    if (token != NULL)
        strcpy(x->DOB, token);

    token = strtok(NULL, "|");
    if (token != NULL)
        x->canNang = atof(token);

    token = strtok(NULL, "|");
    if (token != NULL)
        x->chieuCao = atof(token);
}

void docThongTinTuFile(const char *tenTep, SinhVien a[], int *n) {
    FILE *file = fopen(tenTep, "r");
    if (file == NULL) {
        perror("Không thể mở tệp tin");
        exit(1);
    }

    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Xử lý thông tin từ dòng line và lưu vào mảng a
        Nhap(&a[*n], line);
        (*n)++;
    }

    printf("Da nhap thong tin tu file %s\n", tenTep);
    fclose(file);
}

void nhapThemThongTin(SinhVien* x)
{
    getchar();
    printf("Ho va ten sinh vien: "); gets(x->ten);
    printf("Chon gioi tinh: ");
    int gt;
    printf("1. Nam    2. Nu (Nhap 1 hoac 2): "); scanf("%d", &gt);
    if (gt == 1) {
        strcpy(x->gioiTinh, "Nam");
    } else if (gt == 2) {
        strcpy(x->gioiTinh, "Nu");
    } else printf("Nhap khong hop le, vui long nhap lai !!\n");
    getchar();
    printf("Lop: "); gets(x->lop);
    printf("GPA: "); scanf("%lf", &x->gpa);
    if (x->gpa < 0 || x->gpa > 4.0) {    
        while(x->gpa < 0 || x->gpa > 4.0) {
            printf("Nhap GPA khong hop le, 0 <= GPA <= 4 !!\n");
            printf("GPA: "); scanf("%lf", &x->gpa);
        }
    }
    printf("Can nang (kg): "); scanf("%lf", &x->canNang);
    printf("Chieu cao (cm): "); scanf("%lf", &x->chieuCao);
    getchar();
    printf("Dia chi: "); gets(x->diaChi);
    printf("Ngay thang nam sinh (dd/mm/yyyy): "); scanf("%s", &x->DOB);
    
    taoMaSV(x);
    capEmail(x);
}

