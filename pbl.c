/*
DỰ ÁN PBL1: LẬP TRÌNH TÍNH TOÁN
Chủ đề: Xây dựng chương trình quản lý sinh viên
Nhóm: 
Người thực hiện: Lương Văn Võ & Nguyễn Đặng Bảo Nguyên
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

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

// ham cap ma sinh vien 
void taoMaSV(SinhVien *x) {
    static int counter = 224; 
    sprintf(x->maSV, "102230%d", counter);
    counter++; 
}

// ham cap email cho sinh vien
void capEmail(SinhVien *x) 
{
    sprintf(x->email, "%s@sv1.dut.udn.vn", x->maSV);
}

// Nhap thong tin sinh vien va tra ve sinh vien sau khi nhap
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

// ham tinh BMI
void tinh_BMI(SinhVien *x) { 
    double chieuCao_meters = x->chieuCao / 100.0;
    x->BMI = x->canNang / pow(chieuCao_meters, 2);
}

// ham in thong tin sinh vien
void in(SinhVien *x, int n)
{
    printf("\t%-22s\t%-5s\t%-30s\t%-10s\t%-10s\t%.2lf\t%s\t         %-20s\n", x->ten,x->maSV,x->email, x->gioiTinh, x->lop, x->gpa, x->DOB, x->diaChi);   
}

// ham in thong tin suc khoe sinh vien
void inSucKhoe(SinhVien *x, int n)
{
    tinh_BMI(x);
    printf("\t%-22s\t%-5s\t%-10s\t%-10s  %s\t           %.2lf cm\t %.2lf kg\t %.2lf\n", x->ten,x->maSV, x->gioiTinh, x->lop, x->DOB, x->chieuCao, x->canNang, x->BMI);
}

//ham sap xep theo ten
// Hàm để tách phần họ và tên từ chuỗi hoTen và lưu vào mảng ten
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
int soSanhTenSinhVien(struct SinhVien *sv1, struct SinhVien *sv2) {
    char tenSV1[100], tenSV2[100];
    tachHoTen(sv1->ten, tenSV1);
    tachHoTen(sv2->ten, tenSV2);
    return strcasecmp(tenSV1, tenSV2);
}

// Hàm sắp xếp sinh viên theo tên
void sapXepTheoTen(struct SinhVien a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (soSanhTenSinhVien(&a[i], &a[j]) > 0) {
                // Hoán đổi vị trí của hai sinh viên
                struct SinhVien temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
//     In danh sách sau khi sap xep
    printf("Danh sach sinh vien da sap xep: \n");
    printf("STT\tHo va ten\t        Ma sinh vien\tEmail\t                        Gioi tinh\tLop\t        GPA\tNgay thang nam sinh \t Dia chi\n");
    for (int i = 0; i < n; i++) {
        printf("%d", i + 1);
        in(&a[i], n);
    }
}

// xuat danh sach sinh vien ra file   
void xuatFile(SinhVien *x, int n) {
    for (int i = 0; i < n; i++) {
        if ((strlen(x[i].maSV) == 0) || (strlen(x[i].email) == 0)) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien truoc khi xuat danh sach\n");
            return;
        }
    }
    printf("Da xuat danh sach sinh vien ra file\n");
    FILE *outputFile = fopen("danhSachSinhVien.txt", "w");
    if (outputFile) {
        fprintf(outputFile, "\t\t\t Danh sach sinh vien \t\t\n");
        fprintf(outputFile, "STT\tHo va ten\t        Ma sinh vien\tEmail\t                        Gioi tinh\tLop\t        GPA\tNgay thang nam sinh \t Dia chi\n");

        for (int i = 0; i < n; i++) {
            tinh_BMI(&x[i]);
            fprintf(outputFile, "%-3d\t%-22s\t%-5s\t%-30s\t%-10s\t%-10s\t%.2lf\t%s\t %17s\n",
                                i + 1, x[i].ten, x[i].maSV, x[i].email, x[i].gioiTinh, x[i].lop, x[i].gpa, x[i].DOB, x[i].diaChi);
        }
        fclose(outputFile);
    }
}

// ham de chuyen xau tat ca thanh chu thuong (VD: HELLO -> hello)
void toLowerCase(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = tolower(str[i]); // Chuyển đổi ký tự thành chữ thường
        i++;
    }
}

// tim kiem theo ten
void timKiemTheoTen(SinhVien a[], int n, char name[]) {
    int find = 0;
    printf("STT\tHo va ten\t        Ma sinh vien\tEmail\t                        Gioi tinh\tLop\t        GPA\tNgay thang nam sinh \t Dia chi\n");
    for (int i = 0; i < n; i++) {
        char temp[200];
        strcpy(temp, a[i].ten);
        toLowerCase(temp);
        // Su dung strstr de kiem tra tên có xuat hien trong tên sinh viên không
        if (strstr(temp, name) != NULL) {
            printf("%d", i + 1);
            in(&a[i], n);
            find = 1;
        }
    }
    if (find == 0) {
        printf("Khong tim thay sinh vien\n");
    }
}

// tim kiem theo ma SV
void timKiemTheoMaSV(SinhVien a[], int n, char ID[])
{
    int find = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(ID, a[i].maSV) == 0) {
            printf("STT\tHo va ten\t        Ma sinh vien\tEmail\t                        Gioi tinh\tLop\t        GPA\tNgay thang nam sinh \t Dia chi\n");
            printf("%d", i + 1);
            in(&a[i], n);
            find = 1;
        }
    }
    if (find == 0) {
        printf("Khong tim thay sinh vien\n");
    }
}

// xoa sinh vien theo ten (chi can ten)
void xoaThongTin(SinhVien a[], int* n, char ID[]) {
    for (int i = 0; i < *n; i++) {
        if (strcmp(a[i].maSV, ID) == 0) {
            for (int j = i; j < *n - 1; j++) {
                a[j] = a[j + 1];
            }
            (*n)--;
            break;
        }
    }
}

//Sap xep sinh vien theo gpa giam dan
void sapXepTheoGPA(SinhVien a[], int n)
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
    printf("Danh sach sinh vien da sap xep: \n");
    printf("STT\tHo va ten\t        Ma sinh vien\tEmail\t                        Gioi tinh\tLop\t        GPA\tNgay thang nam sinh \t Dia chi\n");
    for (int i = 0; i < n; i++) {
        printf("%d", i + 1);
        in(&a[i], n);
    }
}

void gotoxy(int x,int y)
{
	COORD CRD;
    CRD.X = x;
    CRD.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CRD);
}

int main()
{
    SinhVien a[1000];
    int n;
    char pass[20]="pbl1\0";
    char pa[20];
    system("color f0");
    gotoxy(53,9);
	printf("DANG NHAP(NHAN ENTER SAU KHI NHAP MAT KHAU)");
	gotoxy(55,10);
	printf("____________________________________");
	gotoxy(55,11);
	printf("|                                  |");
	gotoxy(55,12);
	printf("|__________________________________|");
	gotoxy(70,11);
    gets(pa);
            if (strcmp(pass,pa)==0){
                system("cls");
                    while (1) {
        printf("\n\t    --DO AN LAP TRINH TINH TOAN--\t\t\t\n");
        printf("THUC HIEN BOI: LUONG VAN VO & NGUYEN DANG BAO NGUYEN\n\n");
        printf("-----QUAN LY DANH SACH SINH VIEN-----\n");
        printf("1. Nhap danh sach sinh vien\n");
        printf("2. Cap ma sinh vien\n");
        printf("3. Cap email sinh vien\n");
        printf("4. Tim kiem sinh vien\n");
        printf("5. Xoa sinh vien theo ma sinh vien\n");
        printf("6. Sap xep sinh vien\n");
        printf("7. Hien thi danh sach sinh vien\n");
        printf("8. Xuat file danh sach sinh vien\n");
        printf("9. Danh sach sinh vien nhan hoc bong\n");
        printf("0. Thoat !\n");
        printf("--------------------------------------\n\n");
        printf("Nhap lua chon: ");
        int lc; 
        scanf("%d", &lc);
        if (lc == 1) {
            FILE *file = fopen("sinhvien.txt", "r"); // Mở tệp tin để đọc
            if (file == NULL) {
                perror("Không thể mở tệp tin");
                return 1;
    }
        char line[1000];
        while (fgets(line, sizeof(line), file) != NULL) {
            Nhap(&a[n++], line);
    }
        printf("Da nhap thong tin tu file\n");
        fclose(file);
        }
        else if (lc == 2) {
            for (int i = 0; i < n; i++) {
                taoMaSV(&a[i]);
            }
            printf("Da cap ma sinh vien\n");
        }
        else if (lc == 3) {
            int temp = 0;
            for (int i = 0; i < n; i++) {
            if (strlen(a[i].maSV) == 0) {
            printf("Ma sinh vien chua duoc cap, vui long cap ma sinh vien truoc khi cap email\n");
            temp = 1;
            break;
            }  
        }
        if (temp == 0) {
           for (int i = 0; i < n; i++) {
            capEmail(&a[i]);
           }
           printf("Da cap email sinh vien\n");
        }
        }
        
        else if (lc == 4) {
            int choice;
            printf("1. Tim kiem sinh vien theo ten sinh vien\n");
            printf("2. Tim Kiem sinh vien theo ma sinh vien\n\n");
            printf("Vui long chon lua chon cua ban: "); scanf("%d", &choice);
            if (choice == 1) {
            int temp = 0;
            for (int i = 0; i < n; i++) {
            if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi tim kiem\n");
            temp = 1;
            break;
            }  
        }

            if (temp == 0){
                char name[100];
                printf("Nhap ten sinh vien can tim kiem: ");
                getchar();
                gets(name);
                timKiemTheoTen(a, n, name);
            }
        }
             else if (choice == 2) {
                int temp = 0;
            for (int i = 0; i < n; i++) {
            if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi tim kiem\n");
            temp = 1;
            break;
            }  
        }
         if (temp == 0){
                printf("Nhap ma cua sinh vien can tim kiem: ");
                char ID[20];
                getchar();
                gets(ID);
                timKiemTheoMaSV(a, n, ID);
            }
        }
    }
        else if (lc == 5) {
            int temp = 0;
            for (int i = 0; i < n; i++) {
            if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc xoa\n");
            temp = 1;
            break;
            }  
        }
         if (temp == 0){
            char ID[20];
            printf("Nhap ma sinh vien can xoa: "); 
            getchar();
            gets(ID);
            xoaThongTin(a, &n, ID);
            printf("Da xoa thong tin cua sinh vien co ma sinh vien %s\n", ID);
        }
    }
        else if (lc == 6) {
            int choice;
            printf("1. Sap xep sinh vien co GPA giam dan\n");
            printf("2. Sap xep sinh vien theo ten (tu a - z)\n\n");
            printf("Vui long chon lua chon cua ban: "); scanf("%d", &choice);
            if (choice == 1) {
                 int temp = 0;
                 for (int i = 0; i < n; i++) {
                if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
                printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi sap xep\n");
                temp = 1;
                 break;
            } 
                 } 
             if(temp==0){
                sapXepTheoGPA(a, n);
               }
            }
             else if (choice == 2) {
                int temp = 0;
                 for (int i = 0; i < n; i++) {
                if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
                printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi sap xep\n");
                temp = 1;
                 break;
            }
                 } 
            if(temp==0) {
                sapXepTheoTen(a, n);
            }
        }
          }
        
        else if (lc == 7) {
            int choice;
            printf("1. Danh sach thong tin sinh vien\n");
            printf("2. Danh sach suc khoe sinh vien\n\n");
            printf("Vui long chon lua chon cua ban: "); scanf("%d", &choice);
            if (choice == 1) {
            int temp = 0;
            for (int i = 0; i < n; i++) {
            if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi xuat danh sach\n");
            temp = 1;
            break;
            }  
        }
        if (temp == 0) {
            printf("\t\t\tDanh sach sinh vien\t\t\t\n");
            printf("STT\tHo va ten\t        Ma sinh vien\tEmail\t                        Gioi tinh\tLop\t        GPA\tNgay thang nam sinh \t Dia chi\n");
            for (int i = 0; i < n; i++) {
                printf("%d", i + 1);
                in(&a[i], n);
            }
        }
            } else if (choice == 2) {
                int temp = 0;
            for (int i = 0; i < n; i++) {
            if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi xuat danh sach\n");
            temp = 1;
            break;
            }  
        }
         if (temp == 0){
                printf("\t\tThong tin suc khoe sinh vien\t\t\t\n");
                printf("STT\tHo va ten\t        Ma sinh vien\tGioi tinh\tLop\t    Ngay thang nam sinh\t   Chieu cao\t Can nang \t BMI\n");
                for (int i = 0; i < n; i++) {
                    printf("%d", i + 1);
                    inSucKhoe(&a[i], n);
                }
            }
        }
        }
        else if (lc == 8) {
            int temp = 0;
            for (int i = 0; i < n; i++) {
            if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi xuat danh sach\n");
            temp = 1;
            break;
            }  
        }
         if (temp == 0){
            xuatFile(a, n); 
          }
        }
        else if (lc == 9) {
            int temp = 0;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (a[i].gpa < a[j].gpa) {
                        temp = 1;
                        break;
                    }
                }
            }
            if (temp == 0) {
            printf("\t\t\tDanh sach sinh vien nhan hoc bong\t\t\t\n");
            printf("STT\tHo va ten\t        Ma sinh vien\tEmail\t                        Gioi tinh\tLop\t        GPA\tNgay thang nam sinh \t Dia chi\n");
            for (int i = 0; i < 15; i++) {
                printf("%d", i + 1);
                in(&a[i], n);
            }
            } else if (temp == 1) {
                printf("Ban phai sap xep danh sach sinh vien co diem GPA tu cao xuong thap\n");
            }     
        }
        else if (lc == 0) {
            break;
        }
          }
             }
         else {
            printf("\n\n\t\t\t\t\t\t\tVUI LONG KIEM TRA LAI MAT KHAU!");
            return 0;
        }
    return 0;
}