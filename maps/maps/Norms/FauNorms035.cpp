#include "FauNorms035.h"


//Переопределенные методы
/*virtual*/ void FauNorms035::Tr_Vbr(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) && TestName.contains(Vbr))
    {
        CriteriumDown = 7.0; CriteriumUp = 30.0;
    }
    //Ap
    else if(TestName.contains(Ap) && TestName.contains(Vbr))
    {
        CriteriumDown = -30.0; CriteriumUp = -7.0;
    }
    //Rn
    else if(TestName.contains(Rn) && TestName.contains(Vbr))
    {
        CriteriumDown = 7.0; CriteriumUp = 30.0;
    }
    //Rp
    else if(TestName.contains(Rp) && TestName.contains(Vbr))
    {
        CriteriumDown = -30.0; CriteriumUp = -7.0;
    }
    //Hn
    else if(TestName.contains(Hn) && TestName.contains(Vbr))
    {
        CriteriumDown = 7.0; CriteriumUp = 30.0;
    }
    //Hp
    else if(TestName.contains(Hp) && TestName.contains(Vbr))
    {
        CriteriumDown = -30.0; CriteriumUp = -7.0;
    }
}
/*virtual*/ void FauNorms035::Tr_DSleak(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //TrAn
    if(TestName.contains(An) &&
      (TestName.contains(DSleak) ||
      (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30)*LEN;
        CriteriumUp = 1.0*(1e-10)*LEN;
    }
    //TrAp
    else if(TestName.contains(Ap) &&
      (TestName.contains(DSleak) ||
      (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = -1.0*(1e-10)*LEN;
        CriteriumUp = 0.0;// -1.0*(1e-30)*LEN;
    }
    //TrRn
    else if(TestName.contains(Rn) &&
      (TestName.contains(DSleak) ||
      (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = 0.0; //1.0*(1e-30)*LEN;
        CriteriumUp = 1.0*(1e-10)*LEN;
    }
    //TrRp
    else if(TestName.contains(Rp) &&
      (TestName.contains(DSleak) ||
      (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = -1.0*(1e-10)*LEN;
        CriteriumUp = 0.0;//-1.0*(1e-30)*LEN;
    }
    //TrHn
    else if(TestName.contains(Hn) &&
      (TestName.contains(DSleak) ||
      (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30)*LEN;
        CriteriumUp = 1.0*(1e-10)*LEN;
    }
    //TrHp
    else if(TestName.contains(Hp) &&
      (TestName.contains(DSleak) ||
       (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = -1.0*(1e-10)*LEN;
        CriteriumUp = 0.0;// -1.0*(1e-30)*LEN;
    }
}
/*virtual*/ void FauNorms035::Tr_DSw_leak(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //TrAn
    if(TestName.contains(An) &&
      (TestName.contains(DSw_leak) ||
      (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30);
        CriteriumUp = 1.0*(1e-10);
    }
    //TrAp
    else if(TestName.contains(Ap) &&
      (TestName.contains(DSw_leak) ||
      (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = -1.0*(1e-10);
        CriteriumUp = 0.0;// -1.0*(1e-30);
    }
    //TrRn
    else if(TestName.contains(Rn) &&
      (TestName.contains(DSw_leak) ||
      (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30);
        CriteriumUp = 1.0*(1e-10);
    }
    //TrRp
    else if(TestName.contains(Rp) &&
      (TestName.contains(DSw_leak) ||
      (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = -1.0*(1e-10);
        CriteriumUp = 0.0;// -1.0*(1e-30);
    }
    //TrHn
    else if(TestName.contains(Hn) &&
      (TestName.contains(DSw_leak) ||
      (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30);
        CriteriumUp = 1.0*(1e-10);
    }
    //TrHp
    else if(TestName.contains(Hp) &&
      (TestName.contains(DSw_leak) ||
       (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = -1.0*(1e-10);
        CriteriumUp = 0.0; // -1.0*(1e-30);
    }
}
/*virtual*/ void FauNorms035::Tr_DScurrent(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = 3.75*(1e-4)*LEN; CriteriumUp = 5.2*(1e-4)*LEN;
    }
    //Ap
    else if(TestName.contains(Ap) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4)*LEN; CriteriumUp = -2.0*(1e-4)*LEN;
    }
    //Rn
    else if(TestName.contains(Rn) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = 3.75*(1e-4)*LEN; CriteriumUp = 5.2*(1e-4)*LEN;

    }
    //Rp
    else if(TestName.contains(Rp) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4)*LEN; CriteriumUp = -2.0*(1e-4)*LEN;
    }
    //Hn
    else if(TestName.contains(Hn) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = 3.75*(1e-4)*LEN; CriteriumUp = 5.2*(1e-4)*LEN;
    }
    //Hp
    else if(TestName.contains(Hp) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4)*LEN; CriteriumUp = -2.0*(1e-4)*LEN;
    }
}
/*virtual*/ void FauNorms035::Tr_DSw_driver(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //TrAn
    if(TestName.contains(An) &&
      (TestName.contains(DSw_driver) ||
      (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = 3.75*(1e-4); CriteriumUp = 5.2*(1e-4);
    }
    //TrAp
    else if(TestName.contains(Ap) &&
      (TestName.contains(DSw_driver) ||
      (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4); CriteriumUp = -2.0*(1e-4);
    }
    //TrRn
    else if(TestName.contains(Rn) &&
      (TestName.contains(DSw_driver) ||
      (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = 3.75*(1e-4); CriteriumUp = 5.2*(1e-4);
    }
    //TrRp
    else if(TestName.contains(Rp) &&
      (TestName.contains(DSw_driver) ||
      (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4); CriteriumUp = -2.0*(1e-4);
    }
    //TrHn
    else if(TestName.contains(Hn) &&
      (TestName.contains(DSw_driver) ||
      (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = 3.75*(1e-4); CriteriumUp = 5.2*(1e-4);
    }
    //TrHp
    else if(TestName.contains(Hp) &&
      (TestName.contains(DSw_driver) ||
      (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4); CriteriumUp = -2.0*(1e-4);
    }
}



