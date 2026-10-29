#include "InvoiceController.h"
#include <sstream>

using namespace std;

InvoiceController::InvoiceController()
    : invoiceRepo("data/invoice.txt"), 
      contractRepo("data/contract.txt"), 
      internetRepo("data/internet.txt"),
      installationRepo("data/data_phieulapdat.txt"),
      districtRepo("data/data_khuvuc.txt") {}

// 1. Phuong thuc lay hoa don thang gan nhat cua mot hop dong
Invoice* InvoiceController::getLastInvoice(string contractId) {
    invoiceRepo.reloadData();
    string maxInvId = "";
    int maxDateVal = -1;

    for (auto& inv : invoiceRepo.getData()) {
        if (inv.getContractId() == contractId) {
            int dateVal = Invoice::dateToNumber(inv.getDueDate().empty() ? inv.getInvoiceDate() : inv.getDueDate());
            if (dateVal > maxDateVal) {
                maxDateVal = dateVal;
                maxInvId = inv.getId();
            }
        }
    }
    if (!maxInvId.empty()) {
        return invoiceRepo.searchId(maxInvId);
    }
    return nullptr;
}

// 2. Lay ngay lap dat tu phieu lap dat hoan thanh (status = 1)
string InvoiceController::getInstallationDate(string contractId) {
    installationRepo.reloadData();
    for (auto& pld : installationRepo.getData()) {
        if (pld.getIdContract() == contractId && pld.getStatus() == 1) {
            return pld.getDate();
        }
    }
    return "";
}

// 3. Tu dong cap nhat hoa don qua han (Overdue)
void InvoiceController::autoUpdateOverdueStatus() {
    invoiceRepo.reloadData();
    string today = Invoice::getCurrentDate();
    bool changed = false;
    for (auto& inv : invoiceRepo.getData()) {
        if (inv.getPaymentStatus() == "Unpaid" && Invoice::compareDate(inv.getDueDate(), today)) {
            inv.setPaymentStatus("Overdue");
            changed = true;
        }
    }
    if (changed) {
        invoiceRepo.saveChange();
    }
}

// Ham hien thi MenuHoaDon
void InvoiceController::run() {
    autoUpdateOverdueStatus();
    int choice = -1;
    do {
        cout << "\n==========QUAN LY HOA DON CUOC==========" << endl;
        cout << "1. Lap hoa don cuoc moi" << endl;
        cout << "2. Hien thi danh sach toan bo hoa don" << endl;
        cout << "3. Cap nhat trang thai thanh toan" << endl;
        cout << "4. Xoa hoa don" << endl;
        cout << "0. Quay lai Menu chinh" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Lua chon cua ban: ";

        string richChoice;
        getline(cin, richChoice);
        try {
            size_t pos;
            choice = stoi(richChoice, &pos);
            if (pos != richChoice.size()) choice = -1;
        } catch (...) {
            choice = -1;
        }

        switch (choice) {
            case 1: addInvoice(); break;
            case 2: displayAllInvoices(); break;
            case 3: updatePaymentStatus(); break;
            case 4: deleteInvoiceByContractId(); break;
            case 0: cout << "Dang quay lai Menu chinh ..." << endl; break;
            default: cout << "Lua chon khong hop le! Vui long quay lai." << endl; break;
        }
    } while (choice != 0);
}

void InvoiceController::addInvoice() {
    contractRepo.reloadData();
    internetRepo.reloadData();
    installationRepo.reloadData();
    districtRepo.reloadData();
    invoiceRepo.reloadData();

    // 0. HIEN THI DANH SACH HOP DONG HIEN CO
    cout << "\n========== DANH SACH HOP DONG HIEN TAI ==========" << endl;
    auto listHd = contractRepo.getData();
    if (listHd.empty()) {
        cout << "\n[THONG BAO]: Chua co hop dong nao trong he thong!" << endl;
        return;
    }
    cout << left << setw(15) << "Ma hop dong"
         << "| " << setw(15) << "Ma khach hang"
         << "| " << setw(10) << "Ma goi"
         << "| " << setw(12) << "Ma khu vuc"
         << "| " << setw(12) << "Ngay ky"
         << "| " << setw(10) << "Ky han"
         << "| " << setw(15) << "Ngay het han"
         << "| " << setw(16) << "Trang thai"
         << "| " << "Ghi chu" << endl;
    cout << string(140, '-') << endl;
    for (auto obj : listHd) {
        obj.showToConsole();
    }

    cout << "\n========== LAP HOA DON CUOC MOI ==========" << endl;
    string contractId;
    contract* hd = nullptr;

    // NHAP VA KIEM TRA MA HOP DONG
    while (true) {
        cout << "\nNhap ma hop dong can lap hoa don (Nhap '0' de quay lai): ";
        getline(cin, contractId);
        if (contractId == "0") return;

        for (char& c : contractId) c = toupper(static_cast<unsigned char>(c));

        hd = contractRepo.searchId(contractId);
        if (hd == nullptr) {
            cout << "[LOI]: Ma hop dong '" << contractId << "' khong ton tai! Vui long nhap lai!" << endl;
            continue;
        }
        break;
    }

    // =========================================================================
    // BUOC 1: KIEM TRA DIEU KIEN PHIEU LAP DAT (NGHIEM THU) & KHU VUC (DISTRICT)
    // =========================================================================
    // 1.1 Tim phieu lap dat da hoan thanh (getStatus() == 1)
    string installDate = "";
    for (auto& pld : installationRepo.getData()) {
        if (pld.getIdContract() == contractId && pld.getStatus() == 1) {
            installDate = pld.getDate();
            break;
        }
    }
    if (installDate.empty()) {
        cout << "\n[TU CHOI XUAT HOA DON]: Hop dong '" << contractId 
             << "' chua co Phieu lap dat hoan thanh nghiem thu (Status = 1)!" << endl;
        cout << "=> He thong chi xuat hoa don sau khi da lap dat va nghiem thu thanh cong." << endl;
        return;
    }

    // 1.2 Kiem tra ha tang khu vuc va trang thai khu vuc (district::getStatus)
    district* dist = districtRepo.searchId(hd->getAreaId());
    if (dist == nullptr) {
        cout << "\n[LOI HE THONG]: Khong tim thay thong tin khu vuc/tram mang '" 
             << hd->getAreaId() << "' cua hop dong!" << endl;
        return;
    }

    cout << "\n[THONG TIN HA TANG MANG / KHU VUC]:" << endl;
    cout << "+ Ma khu vuc        : " << dist->getId() << endl;
    cout << "+ Ten khu vuc       : " << dist->getDistrict() << endl;
    cout << "+ Tram quan ly      : " << dist->getStation() << endl;
    cout << "+ Bang thong tram   : " << dist->getMaxBandWidth() << " Mbps" << endl;

    if (dist->getStatus() == 1) {
        cout << "\n[CANH BAO KHU VUC]: Tram quan ly '" << dist->getStation() 
             << "' (Khu vuc " << dist->getDistrict() 
             << ") dang o trang thai 'Canh Bao' (Qua tai bang thong)!" << endl;
        cout << "=> Chat luong duong truyen tai khu vuc nay co the bi suy giam." << endl;
        cout << "Ban co muon tiep tuc lap hoa don cho hop dong o khu vuc nay khong? (y/n): ";
        string tiepTuc;
        getline(cin, tiepTuc);
        if (tiepTuc != "y" && tiepTuc != "Y") {
            cout << "\n[THONG BAO]: Da huy thao tac lap hoa don do khu vuc dang canh bao!" << endl;
            return;
        }
    } else {
        cout << "+ Trang thai khu vuc: On Dinh (An toan de lap hoa don)" << endl;
    }

    // =========================================================================
    // BUOC 2: KIEM TRA HOA DON TRUOC DO (getLastInvoice)
    // =========================================================================
    Invoice* lastInv = getLastInvoice(contractId);
    double noCu = 0.0;

    if (lastInv != nullptr) {
        bool chuaThanhToan = (lastInv->getPaymentStatus() == "Unpaid" || lastInv->getPaymentStatus() == "Overdue");

        // Neu con no va hop dong bi khoa (status == 2) -> CHAN
        if (chuaThanhToan && hd->getStatus() == 2) {
            cout << "\n[TU CHOI XUAT HOA DON]: Hop dong dang o trang thai 'Khong hoat dong' (Khoa)" << endl;
            cout << "va hoa don ky truoc (" << lastInv->getInvoiceDate() << ") van chua thanh toan!" << endl;
            cout << "=> Vui long thanh toan no cu hoac mo khoa hop dong truoc khi lap hoa don moi." << endl;
            return;
        }

        // Neu con no nhung hop dong van mo (status == 1) -> CANH BAO & DON NO
        if (chuaThanhToan && hd->getStatus() == 1) {
            noCu = lastInv->getTotalAmount();
            cout << "\n[CANH BAO NO CU]: Hoa don ky truoc (" << lastInv->getInvoiceDate() 
                 << ") chua thanh toan (So tien: " << fixed << setprecision(0) << noCu << " VND)." << endl;
            cout << "=> So tien no cu nay se tu dong duoc cong vao Phu phi (Surcharge) cua hoa don moi." << endl;
        }
    }

    // =========================================================================
    // BUOC 3: XAC DINH MOC A (NGAY LAP HOA DON) VA MOC B (HET HAN HOP DONG)
    // =========================================================================
    string mocA = (lastInv == nullptr) ? installDate : lastInv->getDueDate();
    string mocB = hd->getExpiryDate();
    if (mocB.empty() || mocB == "none") {
        cout << "\n[LOI]: Hop dong chua co ngay het han (Moc B)! Vui long kiem tra lai thong tin hop dong." << endl;
        return;
    }

    cout << "\n---------------- THONG TIN CHU KY CUOC ----------------" << endl;
    cout << "+ Ngay bat dau tinh cuoc (Moc A) : " << mocA << endl;
    cout << "+ Ngay het han hop dong (Moc B)  : " << mocB << endl;

    // =========================================================================
    // BUOC 4: NHAP SO THANG GIA HAN n VA KIEM TRA (A + n < B)
    // =========================================================================
    int n = 1;
    while (true) {
        cout << "+ Nhap so thang gia han hoa don (n thang, nhap 0 de thoat): ";
        string nStr;
        getline(cin, nStr);
        try {
            n = stoi(nStr);
            if (n == 0) return;
            if (n > 0) break;
        } catch (...) {}
        cout << "[LOI]: Vui long nhap so thang hop le (> 0)!" << endl;
    }

    // Tinh moc A + n
    string mocAn = Invoice::addMonthsToDate(mocA, n);

    // KIEM TRA DIEU KIEN BAT BUOC: A + n < B
    if (!Invoice::compareDate(mocAn, mocB)) {
        cout << "\n[TU CHOI XUAT HOA DON]: Han hoa don (A + " << n << " thang = " << mocAn 
             << ") vuot qua hoac bang Ngay het han hop dong (Moc B = " << mocB << ")!" << endl;
        cout << "=> Dieu kien (A + n < B) KHONG THOA MAN! Vui long gia han hop dong truoc khi lap hoa don." << endl;
        return;
    }

    cout << "=> Han thanh toan hoa don moi (Moc A + n): " << mocAn << " (Hop le!)" << endl;

    // Lay goi mang cua hop dong
    internet* in = internetRepo.searchId(hd->getPackageId());
    if (in == nullptr) {
        cout << "\n[LOI HE THONG]: Khong tim thay thong tin goi mang cua hop dong nay!" << endl;
        return;
    }

    // =========================================================================
    // BUOC 5: THIET LAP VA LUU HOA DON
    // =========================================================================
    Invoice inv;
    inv.setContractId(contractId);
    inv.setPackageFee(in->getPrice() * n);
    inv.setInvoiceDate(mocA);
    inv.setDueDate(mocAn);
    inv.setPaymentStatus("Unpaid");
    inv.setPaymentDate("none");

    // Nhap Chiet khau
    double discount = 0.0;
    while (true) {
        cout << "\nNhap chiet khau giam gia (VND, mac dinh 0): ";
        string disStr;
        getline(cin, disStr);
        if (disStr.empty()) { discount = 0.0; break; }
        try {
            discount = stod(disStr);
            if (discount >= 0) break;
        } catch (...) {}
        cout << "[LOI]: Vui long nhap so tien chiet khau hop le (>= 0)!" << endl;
    }
    inv.setDiscount(discount);

    // Nhap Phu phi phat sinh them (neu co)
    double extraSurcharge = 0.0;
    while (true) {
        cout << "Nhap phu phi phat sinh them (VND, mac dinh 0): ";
        string surStr;
        getline(cin, surStr);
        if (surStr.empty()) { extraSurcharge = 0.0; break; }
        try {
            extraSurcharge = stod(surStr);
            if (extraSurcharge >= 0) break;
        } catch (...) {}
        cout << "[LOI]: Vui long nhap phu phi hop le (>= 0)!" << endl;
    }

    inv.setSurcharge(extraSurcharge + noCu);
    inv.generateInvoiceId();
    inv.calculateTotalAmount();

    cout << "\n========== XAC NHAN THONG TIN HOA DON MOI ==========" << endl;
    cout << "+ Ma hoa don     : " << inv.getId() << endl;
    cout << "+ Ma hop dong    : " << inv.getContractId() << endl;
    cout << "+ Khu vuc / Tram : " << dist->getDistrict() << " - Tram: " << dist->getStation() 
         << " (" << (dist->getStatus() == 1 ? "Canh bao qua tai" : "On dinh") << ")" << endl;
    cout << "+ Ngay lap (A)   : " << inv.getInvoiceDate() << endl;
    cout << "+ Han tra (A+n)  : " << inv.getDueDate() << endl;
    cout << "+ Tien goi mang  : " << fixed << setprecision(0) << inv.getPackageFee() << " VND (" << n << " thang)" << endl;
    cout << "+ Chiet khau     : " << fixed << setprecision(0) << inv.getDiscount() << " VND" << endl;
    cout << "+ Phu phi (No cu): " << fixed << setprecision(0) << inv.getSurcharge() << " VND" << endl;
    cout << "=> TONG TIEN PHAI NOP: " << fixed << setprecision(0) << inv.getTotalAmount() << " VND" << endl;
    cout << "----------------------------------------------------" << endl;

    cout << "Xac nhan luu hoa don nay vao he thong? (y/n): ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "y" || confirm == "Y") {
        if (invoiceRepo.create(inv) == 1) {
            cout << "\n[THANH CONG]: Da tao va luu hoa don '" << inv.getId() << "' vao he thong!" << endl;
        } else {
            cout << "\n[LOI]: Trung ma hoa don hoac loi ghi file!" << endl;
        }
    } else {
        cout << "\n[THONG BAO]: Da huy thao tac lap hoa don!" << endl;
    }
}

void InvoiceController::displayAllInvoices() {
    cout << "\n============================================ DANH SACH HOA DON CUOC ============================================" << endl;
    invoiceRepo.reloadData();
    auto list = invoiceRepo.getData(); 
    if (list.empty()) {
        cout << "\n[THONG BAO]: Chua co hoa don nao trong he thong!" << endl;
        return;
    }

    cout << left 
         << setw(20) << "Ma Hoa Don" 
         << "| " << setw(8)  << "Ma HD" 
         << "| " << setw(12) << "Cuoc Goi" 
         << "| " << setw(12) << "Chiet Khau" 
         << "| " << setw(12) << "Phu Phi" 
         << "| " << setw(13) << "Tong Tien" 
         << "| " << setw(12) << "Trang Thai" 
         << "| " << setw(13) << "Ngay Lap" 
         << "| " << setw(13) << "Han Tra" 
         << "| " << setw(12) << "Ngay TT" 
         << endl;
    cout << string(143, '-') << endl;
    for (auto obj : list) {
        obj.showToConsole(); 
    }
}

void InvoiceController::updatePaymentStatus() {
    invoiceRepo.reloadData();
    auto list = invoiceRepo.getData(); 
    if (list.empty()) {
        cout << "\n[THONG BAO]: Chua co hoa don nao trong he thong!" << endl;
        return;
    }
    displayAllInvoices();

    cout << "\n========== CAP NHAT TRANG THAI THANH TOAN ==========" << endl;
    string invId;
    Invoice* inv = nullptr;
    while (true) {
        cout << "\nNhap ma hoa don can cap nhat (Nhap '0' de quay lai): ";
        getline(cin, invId);
        if (invId == "0") return;
        for (char& c : invId) c = toupper(static_cast<unsigned char>(c));

        inv = invoiceRepo.searchId(invId);
        if (inv == nullptr) {
            cout << "[LOI]: Khong tim thay hoa don '" << invId << "'! Vui long nhap lai!" << endl;
            continue;
        }
        break;
    }

    cout << "\nThong tin hoa don hien tai:" << endl;
    cout << "+ Trang thai: " << inv->getPaymentStatus() << endl;
    cout << "+ Tong tien:  " << fixed << setprecision(0) << inv->getTotalAmount() << " VND" << endl;
    cout << "+ Han nop:    " << inv->getDueDate() << endl;

    cout << "\n[CHON TRANG THAI THANH TOAN MOI]:" << endl;
    cout << "1. Paid (Da thanh toan)" << endl;
    cout << "2. Overdue (Qua han thanh toan)" << endl;
    cout << "3. Unpaid (Chua thanh toan)" << endl;
    cout << "0. Huy thao tac" << endl;
    cout << "Nhap lua chon: ";
    string opt;
    getline(cin, opt);

    if (opt == "1") {
        inv->setPaymentStatus("Paid");
        cout << "Nhap ngay thanh toan thuc te (dd/mm/yyyy) [Nhan Enter lay mac dinh hom nay]: ";
        string payDate;
        getline(cin, payDate);
        if (payDate.empty()) payDate = Invoice::getCurrentDate();
        inv->setPaymentDate(payDate);
        invoiceRepo.saveToFile();
        cout << "\n[THANH CONG]: Da cap nhat hoa don '" << invId << "' sang trang thai 'Paid'!" << endl;
    } else if (opt == "2") {
        inv->setPaymentStatus("Overdue");
        inv->setPaymentDate("none");

        cout << "\n[CAP NHAT PHU PHI QUA HAN]:" << endl;
        cout << "+ Phu phi hien tai: " << fixed << setprecision(0) << inv->getSurcharge() << " VND" << endl;
        double extraFee = 0.0;
        while (true) {
            cout << "Nhap so tien phu phi/phat qua han muon cong them (VND, nhan Enter hoac nhap 0 neu khong them): ";
            string feeStr;
            getline(cin, feeStr);
            if (feeStr.empty()) { extraFee = 0.0; break; }
            try {
                extraFee = stod(feeStr);
                if (extraFee >= 0) break;
            } catch (...) {}
            cout << "[LOI]: Vui long nhap so tien phu phi hop le (>= 0)!" << endl;
        }

        inv->setSurcharge(inv->getSurcharge() + extraFee);
        inv->calculateTotalAmount();
        invoiceRepo.saveToFile();
        cout << "\n[THANH CONG]: Da cap nhat hoa don '" << invId << "' sang trang thai 'Overdue' (Qua han)!" << endl;
        if (extraFee > 0) {
            cout << "=> Da cong them " << fixed << setprecision(0) << extraFee << " VND vao phu phi." << endl;
        }
    } else if (opt == "3") {
        inv->setPaymentStatus("Unpaid");
        inv->setPaymentDate("none");
        invoiceRepo.saveToFile();
        cout << "\n[THANH CONG]: Da cap nhat hoa don '" << invId << "' sang trang thai 'Unpaid'!" << endl;
    } else {
        cout << "\n[THONG BAO]: Da huy thao tac cap nhat!" << endl;
        return;
    }

    // Hien thi lai chi tiet trang thai hoa don sau khi cap nhat
    cout << "\n========== THONG TIN HOA DON SAU KHI CAP NHAT ==========" << endl;
    cout << left 
         << setw(20) << "Ma Hoa Don" 
         << "| " << setw(8)  << "Ma HD" 
         << "| " << setw(12) << "Cuoc Goi" 
         << "| " << setw(12) << "Chiet Khau" 
         << "| " << setw(12) << "Phu Phi" 
         << "| " << setw(13) << "Tong Tien" 
         << "| " << setw(12) << "Trang Thai" 
         << "| " << setw(13) << "Ngay Lap" 
         << "| " << setw(13) << "Han Tra" 
         << "| " << setw(12) << "Ngay TT" 
         << endl;
    cout << string(145, '-') << endl;
    inv->showToConsole();
    cout << string(145, '-') << endl;
}

void InvoiceController::deleteInvoiceByContractId() {
    invoiceRepo.reloadData();
    auto list = invoiceRepo.getData(); 
    if (list.empty()) {
        cout << "\n[THONG BAO]: Chua co hoa don nao trong he thong!" << endl;
        return;
    }
    displayAllInvoices();

    cout << "\n========== XOA HOA DON THEO MA HOP DONG ==========" << endl;
    string conId;
    while (true) {
        cout << "\nNhap ma hop dong de xoa hoa don (Nhap '0' de quay lai): ";
        getline(cin, conId);
        if (conId == "0") return;
        for (char& c : conId) c = toupper(static_cast<unsigned char>(c));

        bool tonTai = false;
        for (auto& x : list) {
            if (x.getContractId() == conId) {
                tonTai = true;
                break;
            }
        }
        if (tonTai) break;
        cout << "\n[THONG BAO]: Hop dong '" << conId << "' khong co hoa don nao! Vui long nhap lai!" << endl;
    }

    cout << "\nBan co chac chan muon xoa cac hoa don da thanh toan (Paid) cua hop dong '" << conId << "' khong (y/n)? ";
    string confirm;
    getline(cin, confirm);
    if (confirm == "y" || confirm == "Y") {
        int count = 0;
        for (auto& x : list) {
            if (x.getContractId() == conId && x.getPaymentStatus() == "Paid") {
                invoiceRepo.remove(x.getId());
                count++;
            }
        }
        if (count > 0) {
            cout << "\n[THANH CONG]: Da xoa " << count << " hoa don da thanh toan cua hop dong '" << conId << "'!" << endl;
        } else {
            cout << "\n[THONG BAO]: Khong co hoa don nao o trang thai 'Paid' de xoa (chi duoc xoa hoa don da thanh toan)!" << endl;
        }
    } else {
        cout << "\n[HUY THAO TAC]: Da huy thao tac xoa hoa don!" << endl;
    }
}
