#include "Norms06.h"



void Norms06::Tr_Vt(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) && TestName.contains(Vt))
    {
        CriteriumDown = 0.55; CriteriumUp = 0.80;
    }
    //Ap
    else if(TestName.contains(Ap) && TestName.contains(Vt))
    {
        CriteriumDown = -0.40; CriteriumUp = -0.60;
    }
    //Rn
    else if(TestName.contains(Rn) && TestName.contains(Vt))
    {
        CriteriumDown = 0.55; CriteriumUp = 0.80;
    }
    //Rp
    else if(TestName.contains(Rp) && TestName.contains(Vt))
    {
        CriteriumDown = -0.40; CriteriumUp = -0.60;
    }
    //Hn
    else if(TestName.contains(Hn) && TestName.contains(Vt))
    {
        CriteriumDown = 0.55; CriteriumUp = 0.80;
    }
    //Hp
    else if(TestName.contains(Hp) && TestName.contains(Vt))
    {
        CriteriumDown = -0.40; CriteriumUp = -0.60;
    }
}
void Norms06::Tr_VtRevers(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) && TestName.contains(Vt) && TestName.contains(revers))
    {
        CriteriumDown = 0.1; CriteriumUp = 30.00;
    }
    //Ap
    else if(TestName.contains(Ap) && TestName.contains(Vt) && TestName.contains(revers))
    {
        CriteriumDown = -30.0; CriteriumUp = -0.1;
    }
    //Rn
    else if(TestName.contains(Rn) && TestName.contains(Vt) && TestName.contains(revers))
    {
        CriteriumDown = 0.1; CriteriumUp = 30.0;
    }
    //Rp
    else if(TestName.contains(Rp) && TestName.contains(Vt) && TestName.contains(revers))
    {
        CriteriumDown = -30.00; CriteriumUp = -0.1;
    }
    //Hn
    else if(TestName.contains(Hn) && TestName.contains(Vt) && TestName.contains(revers))
    {
        CriteriumDown = 0.1; CriteriumUp = 30.0;
    }
    //Hp
    else if(TestName.contains(Hp) && TestName.contains(Vt) && TestName.contains(revers))
    {
        CriteriumDown = -30.0; CriteriumUp = -0.1;
    }
}
void Norms06::Tr_Be(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) && TestName.contains(Be))
    {
        CriteriumDown = 0.95*(1e-4); CriteriumUp = 1.5*(1e-4);
    }
    //Ap
    else if(TestName.contains(Ap) && TestName.contains(Be))
    {
        CriteriumDown = 3.00*(1e-5); CriteriumUp = 4.00*(1e-5);
    }
    //Rn
    if(TestName.contains(Rn) && TestName.contains(Be))
    {
        CriteriumDown = 0.95*(1e-4); CriteriumUp = 1.5*(1e-4);
    }
    //Rp
    else if(TestName.contains(Rp) && TestName.contains(Be))
    {
        CriteriumDown = 3.00*(1e-5); CriteriumUp = 4.00*(1e-5);
    }
    //Hn
    if(TestName.contains(Hn) && TestName.contains(Be))
    {
        CriteriumDown = 0.95*(1e-4); CriteriumUp = 1.5*(1e-4);
    }
    //Hp
    else if(TestName.contains(Hp) && TestName.contains(Be))
    {
        CriteriumDown = 3.00*(1e-5); CriteriumUp = 4.00*(1e-5);
    }
}

void Norms06::Tr_DSleak(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{

    //An
    if(TestName.contains(An) &&
      (TestName.contains(DSleak) ||
      (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30)*LEN;
        CriteriumUp = 6.0*(1e-12)*LEN;
    }
    //Ap
    else if(TestName.contains(Ap) &&
      (TestName.contains(DSleak) ||
      (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = -1.0*(1e-11)*LEN;
        CriteriumUp = 0.0;// -1.0*(1e-30)*LEN;
    }
    //Rn
    else if(TestName.contains(Rn) &&
      (TestName.contains(DSleak) ||
      (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = 0.0; //1.0*(1e-30)*LEN;
        CriteriumUp = 6.0*(1e-12)*LEN;
    }
    //Rp
    else if(TestName.contains(Rp) &&
      (TestName.contains(DSleak) ||
      (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = -1.0*(1e-11)*LEN;
        CriteriumUp = 0.0;//-1.0*(1e-30)*LEN;
    }
    //Hn
    else if(TestName.contains(Hn) &&
      (TestName.contains(DSleak) ||
      (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30)*LEN;
        CriteriumUp = 6.0*(1e-12)*LEN;
    }
    //Hp
    else if(TestName.contains(Hp) &&
      (TestName.contains(DSleak) ||
       (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = -1.0*(1e-11)*LEN;
        CriteriumUp = 0.0;// -1.0*(1e-30)*LEN;
    }
}
void Norms06::Tr_DSw_leak(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) &&
      (TestName.contains(DSw_leak) ||
      (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30);
        CriteriumUp = 6.0*(1e-12);
    }
    //Ap
    else if(TestName.contains(Ap) &&
      (TestName.contains(DSw_leak) ||
      (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = -1.0*(1e-11);
        CriteriumUp = 0.0;// -1.0*(1e-30);
    }
    //Rn
    else if(TestName.contains(Rn) &&
      (TestName.contains(DSw_leak) ||
      (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = 0.0;
        CriteriumUp = 6.0*(1e-12);
    }
    //Rp
    else if(TestName.contains(Rp) &&
      (TestName.contains(DSw_leak) ||
      (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = -1.0*(1e-11);
        CriteriumUp = 0.0;// -1.0*(1e-30);
    }
    //Hn
    else if(TestName.contains(Hn) &&
      (TestName.contains(DSw_leak) ||
      (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30);
        CriteriumUp = 6.0*(1e-11);
    }
    //Hp
    else if(TestName.contains(Hp) &&
      (TestName.contains(DSw_leak) ||
       (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = -1.0*(1e-11);
        CriteriumUp = 0.0; // -1.0*(1e-30);
    }
}
void Norms06::Tr_DScurrent(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = 4.2*(1e-4)*LEN; CriteriumUp = 5.2*(1e-4)*LEN;
    }
    //Ap
    else if(TestName.contains(Ap) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4)*LEN; CriteriumUp = -2.3*(1e-4)*LEN;
    }
    //Rn
    else if(TestName.contains(Rn) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = 4.2*(1e-4)*LEN; CriteriumUp = 5.2*(1e-4)*LEN;

    }
    //Rp
    else if(TestName.contains(Rp) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4)*LEN; CriteriumUp = -2.3*(1e-4)*LEN;
    }
    //Hn
    else if(TestName.contains(Hn) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = 4.2*(1e-4)*LEN; CriteriumUp = 5.2*(1e-4)*LEN;
    }
    //Hp
    else if(TestName.contains(Hp) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4)*LEN; CriteriumUp = -2.3*(1e-4)*LEN;
    }
}
void Norms06::Tr_DSw_driver(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) &&
            (TestName.contains(DSw_driver) ||
             (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = 4.2*(1e-4); CriteriumUp = 5.2*(1e-4);
    }
    //Ap
    else if(TestName.contains(Ap) &&
            (TestName.contains(DSw_driver) ||
             (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4); CriteriumUp = -2.3*(1e-4);
    }
    //Rn
    else if(TestName.contains(Rn) &&
            (TestName.contains(DSw_driver) ||
             (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = 4.2*(1e-4); CriteriumUp = 5.2*(1e-4);
    }
    //Rp
    else if(TestName.contains(Rp) &&
            (TestName.contains(DSw_driver) ||
             (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4); CriteriumUp = -2.3*(1e-4);
    }
    //Hn
    else if(TestName.contains(Hn) &&
            (TestName.contains(DSw_driver) ||
             (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = 4.2*(1e-4); CriteriumUp = 5.2*(1e-4);
    }
    //Hp
    else if(TestName.contains(Hp) &&
            (TestName.contains(DSw_driver) ||
             (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4); CriteriumUp = -2.3*(1e-4);
    }
}



