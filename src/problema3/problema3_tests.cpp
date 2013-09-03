#include <iostream>
#include <ctime>

#include "gtest/gtest.h"
#include "problema3.h"

using namespace std;

TEST(problema3, en) {
    Piso p(1, 2);
    p.set(0, 0, Pared);

    EXPECT_EQ(Pared, p.get(0, 0));
    EXPECT_EQ(Libre, p.get(0, 1));
}

TEST(problema3, okPeroQuedanCasillerosLibres) {
/*
    L   L   L
    L   I   SC
    L   SC  I
*/

    Piso p(3,3);
    // en (0, 0) o (0,1) puede haber un sensorVertical
    p.set(0, 0, Libre);
    p.set(0, 1, Libre);
    p.set(0, 2, Libre);
    p.set(1, 0, Libre);
    p.set(1, 1, Importante);
    p.set(1, 2, SensorCuadruple);
    p.set(2, 0, Libre);
    p.set(2, 1, SensorCuadruple);
    p.set(2, 2, Importante);
    bool value = true;
    EXPECT_EQ(value, checkPiso(p));
}

TEST(problema3, chocanSensores) {
/*
    L   L 
    SDV SC 
*/

    Piso p(2,2);
    
    p.set(0, 0, Libre);
    p.set(0, 1, Libre);
    p.set(1, 0, SensorVertical);
    p.set(1, 1, SensorCuadruple);
    bool value = false;
    EXPECT_EQ(value, checkPiso(p));

}

TEST(problema3, todoParedes) {
/* En principio debería devolver true, ya que las 4 paredes darían un conjunto vacío de láseres
    P   P
    P   P 
*/

    Piso p(2,2);
    
    p.set(0, 0, Pared);
    p.set(0, 1, Pared);
    p.set(1, 0, Pared);
    p.set(1, 1, Pared);
    bool value = true;
    EXPECT_EQ(value, checkPiso(p));

}

TEST(problema3, todoParedeMenosUnElementoImportante) {
/* Este caso no tiene solución
    P   P
    P   I 
*/

    Piso p(2,2);
    
    p.set(0, 0, Pared);
    p.set(0, 1, Pared);
    p.set(1, 0, Pared);
    p.set(1, 1, Importante);
    bool value = false;
    EXPECT_EQ(value, checkPiso(p));

}

TEST(problema3, todoImportante) {
/* Este no tiene solución
    I   I
    I   I 
*/

    Piso p(2,2);
    
    p.set(0, 0, Importante);
    p.set(0, 1, Importante);
    p.set(1, 0, Importante);
    p.set(1, 1, Importante);
    bool value = false;
    EXPECT_EQ(value, checkPiso(p));

}

TEST(problema3, esSolucion) {
/*
    I   SC
    SC  I 
*/

    Piso p(2,2);
    
    p.set(0, 0, Importante);
    p.set(0, 1, SensorCuadruple);
    p.set(1, 0, SensorCuadruple);
    p.set(1, 1, Importante);
    bool value = true;
    EXPECT_EQ(value, checkPiso(p));

}


TEST(problema3, sensoresNoTraspasanLaPared) {
/*
    L   SDH L
    I   SDH I
    SC  P   SC
*/

    Piso p(3,3);
    
    p.set(0, 0, Libre);
    p.set(0, 1, SensorHorizontal);
    p.set(0, 2, Libre);
    p.set(1, 0, Importante);
    p.set(1, 1, SensorHorizontal);
    p.set(1, 2, Importante);
    p.set(2, 0, SensorCuadruple);
    p.set(2, 1, Pared);
    p.set(2, 2, SensorCuadruple);
    bool value = true;
    EXPECT_EQ(value, checkPiso(p));

}

//Quedan lugares libres pero no es valida
TEST(problema3, solucionNoValida) {
/*
    L   L   L
    I   P   I
    SC  P   L
*/

    Piso p(3,3);
    
    p.set(0, 0, Libre);
    p.set(0, 1, Libre);
    p.set(0, 2, Libre);
    p.set(1, 0, Importante);
    p.set(1, 1, Pared);
    p.set(1, 2, Importante);
    p.set(2, 0, SensorCuadruple);
    p.set(2, 1, Pared);
    p.set(2, 2, Libre);
    bool value = false;
    EXPECT_EQ(value, checkPiso(p));

}

// // No hay 2 sensores apuntando a los casilleros importantes
TEST(problema3, noApuntan2Sensores) {
/*
    L   L   SC
    I   P   I
    SC  L   L
*/

    Piso p(3,3);
    
    p.set(0, 0, Libre);
    p.set(0, 1, Libre);
    p.set(0, 2, SensorCuadruple);
    p.set(1, 0, Importante);
    p.set(1, 1, Pared);
    p.set(1, 2, Importante);
    p.set(2, 0, SensorCuadruple);
    p.set(2, 1, Libre);
    p.set(2, 2, Libre);
    bool value = false;
    EXPECT_EQ(value, checkPiso(p));

}

TEST(problema3, noApuntan2Sensores2) {
/* Error importante, hay que calcular para importante
    la posibilidad de que no se pueda poner un sensor
    en su área dado que otro apunta a ese lugar específico
    
    L  SDV  L   L
    I  L    P   I
    SC L    L   L
*/

    Piso p(3,4);
    
    p.set(0, 0, Libre);
    p.set(0, 1, SensorVertical);
    p.set(0, 2, Libre);
    p.set(0, 3, Libre);
    p.set(1, 0, Importante);
    p.set(1, 1, Libre);
    p.set(1, 2, Pared);
    p.set(1, 3, Importante);
    p.set(2, 0, SensorCuadruple);
    p.set(2, 1, Libre);
    p.set(2, 2, Libre);
    p.set(2, 3, Libre);
    bool value = false;
    EXPECT_EQ(value, checkPiso(p));
}

TEST(problema3, noApuntanSensoresACasilleroLibre) {
/* Debería dar true, se puede meter un sensor vertical en (0,2)
    L SDV L
    SC L  P
*/
    Piso p(2,3);
    p.set(0, 0, Libre);
    p.set(0, 1, SensorVertical);
    p.set(0, 2, Libre);
    p.set(1, 0, SensorCuadruple);
    p.set(1, 1, Libre);
    p.set(1, 2, Pared);
    bool value = true;
    EXPECT_EQ(value, checkPiso(p));
}

TEST(problema3, EjemploDelEnuncaido) {
    Piso p(8, 8, "###  *##"
                 "#       "
                 "# * #  #"
                 "# * #  #"
                 "        "
                 "### ####"
                 " #     #"
                 "    *  #");
    // p.imprimir();
    // resolver(p);
}

TEST(problema3, MiEjemplo) {
    // Piso p(2, 2, " *"
    //              "  ");
    
    // Piso p(2, 3, " * "
    //              "  *");

    // Piso p(3, 3, " # "
    //              "* *"
    //              " # ");

    // Piso p(3, 3, "  *"
    //              "   "
    //              "   ");

    // Piso p(4, 2, "* "
    //              "# "
    //              "* "
    //              "  ");

    // Piso p(4, 4, "### "
    //              "#   "
    //              "# * "
    //              "# * ");

    // Piso p(5, 5, "###  "
    //              "#    "
    //              "# * #"
    //              "# * #"
    //              "     ");

    Piso p(6, 6, "###  *"
                 "#     "
                 "# * # "
                 "# * # "
                 "      "
                 "### ##");

    // Piso p(6, 7, "###  *#"
    //              "#      "
    //              "# * #  "
    //              "# * #  "
    //              "       "
    //              "### ###");

    // Piso p(7, 7, "###  *#"
    //              "#      "
    //              "# * #  "
    //              "# * #  "
    //              "       "
    //              "### ###"
    //              " # ####");

    // Piso p(7, 7, "###  *#"
    //              "#      "
    //              "# * #  "
    //              "# * #  "
    //              "       "
    //              "### ###"
    //              " #     ");

    // Piso p(7, 8, "###  *##"
    //              "#       "
    //              "# * #  #"
    //              "# * #  #"
    //              "        "
    //              "### ####"
    //              " #     #");

    // Piso p(8, 8, "###  *##"
    //              "#      #"
    //              "# * #  #"
    //              "# * #  #"
    //              "       #"
    //              "### ####"
    //              " #     #"
    //              "####* ##");

    // Piso p(8, 8, "###  *##"
    //              "#       "
    //              "# * #  #"
    //              "# * #  #"
    //              "        "
    //              "### ####"
    //              " #     #"
    //              "    *  #");

    // resolver(p);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
