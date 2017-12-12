#include <gtest/gtest.h>
#include "../include/math_bigint.h"

TEST(arithmeticOperator, plus){
    
    Math::CBigInt bigInt = Math::CBigInt("2");
    Math::CBigInt bigInt2 = Math::CBigInt("4");
    Math::CBigInt bigInt3 = Math::CBigInt();
    bigInt3 = bigInt + bigInt2;
    
    ASSERT_EQ(bigInt3.getNumber(), "6");
    
    bigInt2 = 3456;
    bigInt3 = bigInt + bigInt2;
    
    ASSERT_EQ(bigInt3.getNumber(), "3458");
    
    bigInt = 220544;
    bigInt3 = bigInt + bigInt2;
    
    ASSERT_EQ(bigInt3.getNumber(), "224000");
    
    bigInt = 10;
    bigInt3 = bigInt3 + bigInt;
    
    ASSERT_EQ(bigInt3.getNumber(), "224010");
    
    bigInt = 4;
    bigInt2 = 8;
    bigInt3 = bigInt + bigInt2;
    
    ASSERT_EQ(bigInt3.getNumber(), "12");
    
    bigInt = "10000";
    bigInt2 = "2800";
    bigInt3 = bigInt + bigInt2;
    ASSERT_EQ(bigInt3.getNumber(), "12800");
}

TEST(arithmeticOperator, minus) {
    
    Math::CBigInt bigInt = Math::CBigInt("10");
    Math::CBigInt bigInt2 = Math::CBigInt("4");
    
    ASSERT_EQ((bigInt - bigInt2).getNumber(), "6");
    
    bigInt = Math::CBigInt("1000");
    bigInt2 = Math::CBigInt("999");
    
    ASSERT_EQ((bigInt - bigInt2).getNumber(), "1");
    
    bigInt = Math::CBigInt("10");
    bigInt2 = Math::CBigInt("15");
    
    ASSERT_EQ((bigInt - bigInt2).getNumber(), "5");
    ASSERT_TRUE((bigInt - bigInt2).getSign());
    
    bigInt = "100000";
    bigInt2 = "999";
    
    ASSERT_EQ((bigInt - bigInt2).getNumber(), "99001");
    
    bigInt = "-5";
    bigInt2 = "5";
    
    ASSERT_EQ((bigInt - bigInt2).getNumber(), "10");
    ASSERT_TRUE((bigInt - bigInt2).getSign());
    
    bigInt = "5";
    bigInt2 = "-5";
    
    ASSERT_EQ((bigInt - bigInt2).getNumber(), "10");
    ASSERT_FALSE((bigInt - bigInt2).getSign());
}

// if input is small enough the * operator uses the simple multiplication algorithm
TEST(arithmeticOperator, simpleMultiplication) {
    Math::CBigInt bigInt = Math::CBigInt("9");
    Math::CBigInt bigInt2 = Math::CBigInt("4");
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "36");
    
    bigInt = "0";
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "0");
    
    bigInt = 50;
    bigInt2 = 9L;
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "450");
}

TEST(arithmeticOperator, simpleMultiplicationNegative) {
    Math::CBigInt bigInt = Math::CBigInt("-4");
    Math::CBigInt bigInt2 = Math::CBigInt("2");
    Math::CBigInt result = Math::CBigInt();
    
    result = bigInt * bigInt2;
    
    ASSERT_EQ(result.getNumber(), "8");
    ASSERT_TRUE(result.getSign());
    
    bigInt2 = -2;
    result = bigInt * bigInt2;
    
    ASSERT_EQ(result.getNumber(), "8");
    ASSERT_FALSE(result.getSign());
    
    bigInt = -2;
    bigInt2 = 4;
    result = bigInt * bigInt2;
    ASSERT_EQ(result.getNumber(), "8");
    ASSERT_TRUE(result.getSign());
}

TEST(arithmeticOperator, karatsubaMultiplication) {
    Math::CBigInt bigInt = Math::CBigInt("10");
    Math::CBigInt bigInt2 = Math::CBigInt("10");
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "100");
    
    bigInt = 27;
    bigInt2 = 124;
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "3348");
    
    bigInt = 105;
    bigInt2 = 123;
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "12915");
    
    bigInt = "12345";
    bigInt2 = "6789";
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "83810205");
    
    bigInt = "123456789";
    bigInt2 = "987654321";
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "121932631112635269");
    
    bigInt = "123456789";
    bigInt2 = "987";
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "121851850743");
    
    bigInt = "812398458302402349812093848";
    bigInt2 = "1232342341232459934812919";
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "1001153018118023490350428987359513032114783550822312");
    
    bigInt2 = "123456789";
    bigInt = "987";
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "121851850743");
    
    bigInt= "104438888141315250669175271071662438257996424904738378038423"
            "348328395390797155745684882681193499755834089010671443926283"
            "798757343818579360726323608785136527794595697654370999834036"
            "159013438371831442807001185594622637631883939771274567233468"
            "434458661749680790870580370407128404874011860911446797778359"
            "802900668693897688178778594690563019026094059957945343282346"
            "930302669644305902501597239986771421554169383555988529148631"
            "823791443449673408781187263949647510018904134900841706167509"
            "366833385055103297208826955076998361636941193301521379682583"
            "718809183365675122131849284636812555022599830041234478486259"
            "567449219461702380650591324561082573183538008760862210283427"
            "019769820231316901767800667519548507992163641937028537512478"
            "401490715913545998279051339961155179427110683113409058427288";
    bigInt2 = "798757343818579360726323608785136527794595697654370999834036"
            "159013438371831442807001185594622637631883939771274567233468"
            "434458661749680790870580370407128404874011860911446797778359"
            "802900668693897688178778594690563019026094059957945343282346"
            "930302669644305902501597239986771421554169383555988529148631"
            "823791443449673408781187263949647510018904134900841706167509";
    std::string res = "834213288831226964395752691058262096309869552822518760868137"
                      "649639210139536942144216391417583732251137901454574315084085"
                      "885160786571456013061118804009454763274574706708751022834284"
                      "206512435657597694903299561296871523744043265945324353756117"
                      "477554080221666444967419655343345673560401123529675318804676"
                      "704557607591969211430482284008953406055828000548932849663453"
                      "958177114483435370571675007821710856175940087054430939853882"
                      "414529106264111247186208394225335284802928941901922180965041"
                      "625006597711767014846018475746311333961541762578399798959910"
                      "174526154012930526229135295851090601607397861483613253600700"
                      "723606440363955729365858735115612704020355333000729191182701"
                      "542443872913614945177837530085855402393784239868288467557401"
                      "953917696440831599762472147096752470953088010146090713252162"
                      "303506321921384359890585354420919300096196038013567329071765"
                      "265832755106851065712663440800021378209700851985084895845875"
                      "647719327364315134751073678908221531534841419552555381867139"
                      "114797913838661776715275438712111380516074368722137423109453"
                      "128591570167868597429663918175680165921237572059593518717489"
                      "99158278024907374917237477620667567972695727836841424585592";
    ASSERT_EQ((bigInt * bigInt2).getNumber(), res);
}

TEST(arithmeticOperator, simpleFlooredDivision) {
    Math::CBigInt bigInt = Math::CBigInt("5");
    Math::CBigInt bigInt2 = Math::CBigInt("2");
    Math::CBigInt res = Math::CBigInt();
    
    
    res = bigInt / bigInt2;
    ASSERT_EQ(res.getNumber(), "2");
    ASSERT_FALSE(res.getSign());
    
    bigInt = -5;
    res = bigInt / bigInt2;
    ASSERT_EQ(res.getNumber(), "3");
    ASSERT_TRUE(res.getSign());
    
    bigInt2 = -2;
    res = bigInt / bigInt2;
    ASSERT_EQ(res.getNumber(), "2");
    ASSERT_FALSE(res.getSign());
    
    bigInt = 5;
    res = bigInt / bigInt2;
    ASSERT_EQ(res.getNumber(), "3");
    ASSERT_TRUE(res.getSign());
    
    bigInt = 44415;
    bigInt2 = 45;
    res = bigInt / bigInt2;
    ASSERT_EQ(res.getNumber(), "987");
    ASSERT_FALSE(res.getSign());
    
    bigInt = 42041;
    bigInt2 = 42;
    res = bigInt / bigInt2;
    ASSERT_EQ(res.getNumber(), "1000");
    ASSERT_FALSE(res.getSign());
    
    
    bigInt = 50;
    bigInt2 = 2;
    res = bigInt / bigInt2;
    ASSERT_EQ(res.getNumber(), "25");
    ASSERT_FALSE(res.getSign());
    
    bigInt = "1001153018118023490350428987359513032114783550822312";
    bigInt2 = "121851850743";
    res = bigInt / bigInt2;
    ASSERT_EQ(res.getNumber(), "8216149463577487243011542014355443232488");
}

TEST(arithmeticOperator, simpleCeiledDivision) {
    Math::CBigInt bigInt = Math::CBigInt("5");
    Math::CBigInt bigInt2 = Math::CBigInt("2");
    Math::CBigInt res = Math::CBigInt();
    
    res = res.ceiledDivision(bigInt, bigInt2);
    ASSERT_EQ(res.getNumber(), "3");
    ASSERT_FALSE(res.getSign());
    
    bigInt = -5;
    res = res.ceiledDivision(bigInt, bigInt2);
    ASSERT_EQ(res.getNumber(), "2");
    ASSERT_TRUE(res.getSign());
    
    bigInt2 = -2;
    res = res.ceiledDivision(bigInt, bigInt2);
    ASSERT_EQ(res.getNumber(), "3");
    ASSERT_FALSE(res.getSign());
    
    bigInt = 5;
    res = res.ceiledDivision(bigInt, bigInt2);
    ASSERT_EQ(res.getNumber(), "2");
    ASSERT_TRUE(res.getSign());
}

TEST(arithmeticOperator, modulo) {
    Math::CBigInt bigInt = Math::CBigInt("11");
    Math::CBigInt bigInt2 = Math::CBigInt("5");
    Math::CBigInt res = Math::CBigInt();
    
    
    res = bigInt % bigInt2;
    ASSERT_EQ(res.getNumber(), "1");
    ASSERT_FALSE(res.getSign());
    
    bigInt = -11;
    res = bigInt % bigInt2;
    ASSERT_EQ(res.getNumber(), "4");
    ASSERT_FALSE(res.getSign());
    
    bigInt = 11;
    bigInt2 = -5;
    res = bigInt % bigInt2;
    ASSERT_EQ(res.getNumber(), "4");
    ASSERT_TRUE(res.getSign());
    
    bigInt = -11;
    res = bigInt % bigInt2;
    ASSERT_EQ(res.getNumber(), "1");
    ASSERT_TRUE(res.getSign());
}

TEST(arithmeticOperator, exponentiation) {
    Math::CBigInt bigInt = Math::CBigInt("2");
    Math::CBigInt bigInt2 = Math::CBigInt("3");
    Math::CBigInt res = Math::CBigInt();
    
    res = bigInt ^ bigInt2;
    ASSERT_EQ(res.getNumber(), "8");
    
    bigInt = 2;
    bigInt2 = 50;
    res = bigInt ^ bigInt2;
    
    ASSERT_EQ(res.getNumber(), "1125899906842624");
    
    bigInt = 15;
    bigInt2 = 25;
    res = bigInt.operator^(bigInt2);
    
    ASSERT_EQ(res.getNumber(), "252511682940423488616943359375");
    
    bigInt = 2;
    bigInt2 = 512;
    res = bigInt ^ bigInt2;
    
    ASSERT_EQ(res.getNumber(), "134078079299425970995740249982058461274793658205923933777235"
            "614437217640300735469768018742981669034276900318581864860508"
            "53753882811946569946433649006084096");
    
    bigInt = 2;
    bigInt2 = 4096;
    res = bigInt ^ bigInt2;
    ASSERT_EQ(res.getNumber(), "104438888141315250669175271071662438257996424904738378038423"
            "348328395390797155745684882681193499755834089010671443926283"
            "798757343818579360726323608785136527794595697654370999834036"
            "159013438371831442807001185594622637631883939771274567233468"
            "434458661749680790870580370407128404874011860911446797778359"
            "802900668693897688178778594690563019026094059957945343282346"
            "930302669644305902501597239986771421554169383555988529148631"
            "823791443449673408781187263949647510018904134900841706167509"
            "366833385055103297208826955076998361636941193301521379682583"
            "718809183365675122131849284636812555022599830041234478486259"
            "567449219461702380650591324561082573183538008760862210283427"
            "019769820231316901767800667519548507992163641937028537512478"
            "401490715913545998279051339961155179427110683113409058427288"
            "427979155484978295432353451706522326906139490598769300212296"
            "339568778287894844061600741294567491982305057164237715481632"
            "138063104590291613692670834285644073044789997190178146576347"
            "322385026725305989979599609079946920177462481771844986745565"
            "925017832907047311943316555080756822184657174637329688491281"
            "952031745700244092661691087414838507841192980452298185733897"
            "764810312608590300130241346718972667321649151113160292078173"
            "8033436090243804708340403154190336");
}

TEST(arithmeticOperator, modularExponentiation) {
    Math::CBigInt base = Math::CBigInt("4");
    Math::CBigInt exponent = Math::CBigInt("13");
    Math::CBigInt mod = Math::CBigInt("497");
    Math::CBigInt res = Math::CBigInt();
    
    res = Math::CBigInt::modularExponentiation(base, exponent, mod);
    ASSERT_EQ(res.getNumber(), "445");
    
    base = 13;
    exponent = 2345;
    mod = 5;
    res = Math::CBigInt::modularExponentiation(base, exponent, mod);
    ASSERT_EQ(res.getNumber(), "3");
    
    base = 519230;
    exponent = 841;
    mod = 67;
    res = Math::CBigInt::modularExponentiation(base, exponent, mod);
    ASSERT_EQ(res.getNumber(), "55");
    
    base = 2;
    exponent = 4096;
    mod = 3041;
    res = Math::CBigInt::modularExponentiation(base, exponent, mod);
    ASSERT_EQ(res.getNumber(), "1586");
}