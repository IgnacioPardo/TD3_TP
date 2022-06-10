#include <gtest/gtest.h>

#include "RedSocial.h"

using namespace std;

TEST(RedSocial, vacia) {
    RedSocial rs;
    
    EXPECT_EQ(0, rs.cantidad_amistades());
    EXPECT_EQ(set<int>(), rs.usuarios());
}

TEST(RedSocial, agregar_usuarios_ver_ids) {
    RedSocial rs;

    rs.registrar_usuario("agus", 1);
    rs.registrar_usuario("gerva", 2);
    rs.registrar_usuario("tom", 3);

    set<int> u = {1,2,3};
    EXPECT_EQ(u, rs.usuarios());

    rs.registrar_usuario("vir", 4);
    rs.registrar_usuario("vivi", 5);
    
    u = {1,2,3,4,5};
    EXPECT_EQ(u, rs.usuarios());
}

TEST(RedSocial, agregar_usuarios_ver_alias) {
    RedSocial rs;

    rs.registrar_usuario("tom", 3);
    rs.registrar_usuario("gerva", 2);
    rs.registrar_usuario("agus", 1);

    EXPECT_EQ("tom", rs.obtener_alias(3));
    EXPECT_EQ("gerva", rs.obtener_alias(2));
    EXPECT_EQ("agus", rs.obtener_alias(1));
}

TEST(RedSocial, agregar_usuarios_ver_amigos) {
    RedSocial rs;

    rs.registrar_usuario("tom", 3);
    rs.registrar_usuario("gerva", 2);
    rs.registrar_usuario("agus", 1);

    EXPECT_EQ(0, rs.cantidad_amistades());
    EXPECT_EQ(set<string>(), rs.obtener_amigos(3));
    EXPECT_EQ(set<string>(), rs.obtener_amigos(2));
    EXPECT_EQ(set<string>(), rs.obtener_amigos(1));
}

TEST(RedSocial, eliminar_usuarios_ver_ids) {
    RedSocial rs;

    rs.registrar_usuario("agus", 1);
    rs.registrar_usuario("gerva", 2);
    rs.registrar_usuario("tom", 3);
    rs.registrar_usuario("vir", 4);
    rs.registrar_usuario("vivi", 5);

    rs.eliminar_usuario(2);
    rs.eliminar_usuario(3);

    set<int> u = {1,4,5};
    EXPECT_EQ(u, rs.usuarios());
    
    rs.eliminar_usuario(1);
    rs.eliminar_usuario(4);
    rs.eliminar_usuario(5);

    u = {};
    EXPECT_EQ(u, rs.usuarios());
}

TEST(RedSocial, amigar_usuarios_ver_amigos) {
    RedSocial rs;

    rs.registrar_usuario("agus", 5);
    rs.registrar_usuario("gerva", 4);
    rs.registrar_usuario("tom", 3);
    rs.registrar_usuario("vir", 2);
    rs.registrar_usuario("vivi", 1);

    rs.amigar_usuarios(1,2);

    EXPECT_EQ(1, rs.cantidad_amistades());
    set<string> u = {"vir"};
    EXPECT_EQ(u, rs.obtener_amigos(1));
    u = {"vivi"};
    EXPECT_EQ(u, rs.obtener_amigos(2));

    rs.amigar_usuarios(1,3);
    rs.amigar_usuarios(4,5);

    EXPECT_EQ(3, rs.cantidad_amistades());
    u = {"vir", "tom"};
    EXPECT_EQ(u, rs.obtener_amigos(1));
    u = {"vivi"};
    EXPECT_EQ(u, rs.obtener_amigos(2));
    u = {"vivi"};
    EXPECT_EQ(u, rs.obtener_amigos(3));
    u = {"agus"};
    EXPECT_EQ(u, rs.obtener_amigos(4));
    u = {"gerva"};
    EXPECT_EQ(u, rs.obtener_amigos(5));
}

TEST(RedSocial, desamigar_usuarios_ver_amigos) {
    RedSocial rs;

    rs.registrar_usuario("agus", 5);
    rs.registrar_usuario("gerva", 4);
    rs.registrar_usuario("tom", 3);
    rs.registrar_usuario("vir", 2);
    rs.registrar_usuario("vivi", 1);

    rs.amigar_usuarios(1,2);
    rs.amigar_usuarios(1,3);
    rs.amigar_usuarios(4,5);
    rs.desamigar_usuarios(1,2);

    EXPECT_EQ(2, rs.cantidad_amistades());
    set<string> u = {"tom"};
    EXPECT_EQ(u, rs.obtener_amigos(1));
    u = {};
    EXPECT_EQ(u, rs.obtener_amigos(2));
    u = {"vivi"};
    EXPECT_EQ(u, rs.obtener_amigos(3));
    u = {"agus"};
    EXPECT_EQ(u, rs.obtener_amigos(4));
    u = {"gerva"};
    EXPECT_EQ(u, rs.obtener_amigos(5));
}

TEST(RedSocial, eliminar_usuarios_ver_amigos) {
    RedSocial rs;

    rs.registrar_usuario("agus", 5);
    rs.registrar_usuario("gerva", 4);
    rs.registrar_usuario("tom", 3);
    rs.registrar_usuario("vir", 2);
    rs.registrar_usuario("vivi", 1);

    rs.amigar_usuarios(1,2);
    rs.amigar_usuarios(1,3);
    rs.amigar_usuarios(4,5);

    rs.eliminar_usuario(1);

    EXPECT_EQ(1, rs.cantidad_amistades());
    set<string> u = {};
    EXPECT_EQ(u, rs.obtener_amigos(2));
    u = {};
    EXPECT_EQ(u, rs.obtener_amigos(3));
    u = {"agus"};
    EXPECT_EQ(u, rs.obtener_amigos(4));
    u = {"gerva"};
    EXPECT_EQ(u, rs.obtener_amigos(5));
}

TEST(RedSocial, obtener_id) {
    RedSocial rs;

    rs.registrar_usuario("agus", 5);
    rs.registrar_usuario("gerva", 0);
    rs.registrar_usuario("tom", 27);

    EXPECT_EQ(5, rs.obtener_id("agus"));
    EXPECT_EQ(0, rs.obtener_id("gerva"));
    EXPECT_EQ(27, rs.obtener_id("tom"));
}

TEST(RedSocial, amigar_usuarios_ver_amigos_popular) {
    RedSocial rs;

    rs.registrar_usuario("agus", 5);
    rs.registrar_usuario("gerva", 4);
    rs.registrar_usuario("tom", 3);
    rs.registrar_usuario("vir", 2);
    rs.registrar_usuario("vivi", 1);

    rs.amigar_usuarios(1,2);
    rs.amigar_usuarios(4,5);
    rs.amigar_usuarios(4,3);

    set<string> u = {"agus", "tom"};
    EXPECT_EQ(u, rs.amigos_del_usuario_mas_popular());

    rs.amigar_usuarios(1,3);
    rs.amigar_usuarios(1,5);

    u = {"vir", "tom", "agus"};
    EXPECT_EQ(u, rs.amigos_del_usuario_mas_popular());
}

TEST(RedSocial, desamigar_usuarios_ver_amigos_popular_cambia) {
    RedSocial rs;

    rs.registrar_usuario("agus", 5);
    rs.registrar_usuario("gerva", 4);
    rs.registrar_usuario("tom", 3);
    rs.registrar_usuario("vir", 2);
    rs.registrar_usuario("vivi", 1);

    rs.amigar_usuarios(1,2);
    rs.amigar_usuarios(1,3);
    rs.amigar_usuarios(4,5);
    rs.amigar_usuarios(4,3);
    rs.amigar_usuarios(1,5);
    rs.desamigar_usuarios(5,1);
    rs.desamigar_usuarios(3,1);

    set<string> u = {"agus", "tom"};
    EXPECT_EQ(u, rs.amigos_del_usuario_mas_popular());
}

TEST(RedSocial, desamigar_usuarios_ver_amigos_popular_no_cambia) {
    RedSocial rs;

    rs.registrar_usuario("agus", 5);
    rs.registrar_usuario("gerva", 4);
    rs.registrar_usuario("tom", 3);
    rs.registrar_usuario("vir", 2);
    rs.registrar_usuario("vivi", 1);

    rs.amigar_usuarios(1,2);
    rs.amigar_usuarios(1,3);
    rs.amigar_usuarios(4,5);
    rs.amigar_usuarios(4,3);
    rs.amigar_usuarios(1,5);
    rs.desamigar_usuarios(4,5);
    rs.desamigar_usuarios(4,3);

    set<string> u = {"vir", "tom", "agus"};
    EXPECT_EQ(u, rs.amigos_del_usuario_mas_popular());
}

TEST(RedSocial, eliminar_usuario_ver_amigos_popular_cambia) {
    RedSocial rs;

    rs.registrar_usuario("agus", 5);
    rs.registrar_usuario("gerva", 4);
    rs.registrar_usuario("tom", 3);
    rs.registrar_usuario("vir", 2);
    rs.registrar_usuario("vivi", 1);

    rs.amigar_usuarios(1,2);
    rs.amigar_usuarios(1,3);
    rs.amigar_usuarios(4,5);
    rs.amigar_usuarios(4,3);
    rs.amigar_usuarios(1,5);
    rs.eliminar_usuario(1);

    set<string> u = {"agus", "tom"};
    EXPECT_EQ(u, rs.amigos_del_usuario_mas_popular());
}

TEST(RedSocial, eliminar_usuario_ver_amigos_popular_no_cambia) {
    RedSocial rs;

    rs.registrar_usuario("agus", 5);
    rs.registrar_usuario("gerva", 4);
    rs.registrar_usuario("tom", 3);
    rs.registrar_usuario("vir", 2);
    rs.registrar_usuario("vivi", 1);

    rs.amigar_usuarios(1,2);
    rs.amigar_usuarios(1,3);
    rs.amigar_usuarios(4,5);
    rs.amigar_usuarios(4,3);
    rs.amigar_usuarios(1,5);
    rs.eliminar_usuario(4);

    set<string> u = {"vir", "tom", "agus"};
    EXPECT_EQ(u, rs.amigos_del_usuario_mas_popular());
}