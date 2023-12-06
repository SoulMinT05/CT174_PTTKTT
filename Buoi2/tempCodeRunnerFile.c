au == PA[i].dau || moi.dau == PA[i].cuoi) 
            dem++;
        i++;
    }
    if(dem==3) 
        return 1;
    
    while(i<k && dem<3) {
        if(moi.cuoi == PA[i].dau || moi.cuoi == PA[i].cuoi)
            dem++;