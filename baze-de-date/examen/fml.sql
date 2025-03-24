-- ## Sa se selecteze din tabela angajaţi numai angajatii care au salariul cuprins intre 8000 si 10000
select *
  from angajati
 where salariul between 8000 and 10000;

-- ## Sa se selecteze din tabela angajati numai angajatii care au functia SA_REP
select *
  from angajati
 where id_functie = 'SA_REP';
-- ## Sa se selecteze angajatii care sunt in acelasi departament cu angajatul Smith
select *
  from angajati
 where id_departament = any (
   select id_departament
     from angajati
    where nume = 'Smith'
);

-- ## Modificati conditia de la punctul 2 astfel incat sa fie selectati si cei care au in denumirea functiei atributul ACCOUNT
select *
  from angajati
 where upper(id_functie) = 'SA_REP'
    or upper(id_functie) like '%ACCOUNT%';

-- ## Sa se selecteze toti angajatii pentru care a doua litera din e-mail este A, B sau C
select *
  from angajati
 where substr(
   email,
   2,
   1
) in ( 'A',
       'B',
       'C' );

-- ## Sa se selecteze toti angajatii care au numarul de telefon format din al doilea grup de cifre din 123 (de exemplu: 515.123.4569)
select *
  from angajati
 where substr(
   telefon,
   5,
   3
) = '123';

-- ## Sa se selecteze toti angajatii angajati inainte de 1 ianuarie 2009 (data_angajare)
select *
  from angajati
 where data_angajare <= to_date('01-01-2009','dd-mm-yyyy');

-- ##  Sa se selecteze numele, salariul, denumirea functiei angajatilor şi denumirea departamentului pentru cei care lucreaza în departamentul IT
select a.nume,
       a.salariul,
       f.denumire_functie as functie,
       d.denumire_departament as departament
  from angajati a,
       departamente d,
       functii f
 where a.id_departament = d.id_departament
   and a.id_functie = f.id_functie
   and upper(a.id_functie) like '%IT%';

-- ## Sa se afiseze id departament, denumire departament, salariul minim si numărul de angajati pentru fiecare departament, cu mai mult de 5 angajați
select d.id_departament as id,
       d.denumire_departament as denumire,
       min(a.salariul) as salariul_minim,
       count(a.id_angajat) as nr_angajati
  from angajati a,
       departamente d
 where a.id_departament = d.id_departament
 group by d.id_departament,
          d.denumire_departament
having count(a.id_angajat) > 5;

-- ## Afisati numele si in ordine crescatoare salariile si in ordine descrescatoare data angajarii pentru salariatii din departamentul vânzări (Sales).
select nume,
       salariul
  from angajati
 where upper(id_functie) like '%SA%'
 order by salariul asc,
          data_angajare desc;

-- ## Sa se selecteze numele, functia, comisionul si departamentul angajatilor care nu au comisionul NULL
select nume,
       id_functie,
       comision,
       id_departament
  from angajati
 where comision is not null;

-- Sa se afiseze nr_comanda, data, valoarea comenzii, pentru comenzile incheiate in 1999 cu valoarea totala (sum(cantitate*pret)) mai mare de 2000, în ordinea datei.
select c.id_comanda,
       c.data,
       sum(rc.cantitate * rc.pret) as valoare_totala
  from comenzi c,
       rand_comenzi rc
 where c.id_comanda = rc.id_comanda
   and extract(year from c.data) = 1999
 group by c.id_comanda,
          c.data
having sum(rc.cantitate * rc.pret) > 2000
 order by c.data;

-- Sa se afiseze numarul comenzii, data, valoarea totala comandata  (sum(cantitate*pret)) si sa se calculeze cheltuielile de transport pentru livrarea acestora astfel:
-- -	pentru comenzi cu valoarea de pana la 1000 cheltuielile de transport sa fie de 100
-- -	pentru comenzi cu valoarea 1000  si 2000 cheltuielile de transport sa fie de 200
-- -	pentru comenzi cu valoarea mai mare de 2000 cheltuielile de transport sa fie de 300
select c.id_comanda,
       to_char(
          c.data,
          'dd-mm-yyyy'
       ) as data,
       sum(rc.cantitate * rc.pret) as valoare_totala,
       (
          case
             when sum(rc.cantitate * rc.pret) < 1000                then
                100
             when sum(rc.cantitate * rc.pret) between 1000 and 2000 then
                200
             when sum(rc.cantitate * rc.pret) > 2000                then
                300
             else
                0
          end
       ) as cheltuieli_transport
  from comenzi c,
       rand_comenzi rc
 where c.id_comanda = rc.id_comanda
 group by c.id_comanda,
          c.data;

-- Sa se afiseze id_client, id_produs si cantitatea totala din fiecare produs, vanduta unui client.
select c.id_client,
       rc.id_produs,
       rc.cantitate
  from comenzi c,
       rand_comenzi rc
 where c.id_comanda = rc.id_comanda
 group by c.id_client,
          rc.id_produs,
          rc.cantitate
 order by c.id_client asc;
 
-- Sa se afiseze numele, denumirea departamentului unde lucreaza si nivelul ierarhic pentru toti angajatii care au subordonati si care au aceeasi functie ca angajatul Russell

-- Sa se afiseze numele angajatilor care nu au subalterni si care au aceeasi functie ca angajatul Rogers, nivelul ierarhic si denumirea departamentului unde acestia lucreaza

-- Sa se afiseze departamentele (id_departament si denumire_departament) care au numai angajati cu salariul < 10000

-- Sa se afiseze numele, salariul, data angajarii, denumirea functiei pentru angajatii care au functia Programmer sau Accountant si au fost angajati intre 1995 si 1998.

-- Sa se realizeze o operatie de modificare a pretului la produse astfel incat noul pret sa se mareasca cu 15% pentru toate produsele care au pretul mai mic decat pretul mediu al produsului care contine denumirea cuvantunl sound  (se actualizeaza tabela  rand_comenzi). La final sa se anuleze operatia de actualizare.

-- Sa se afiseze numele, data angajarii, functia actuala si functiile detinute de angajatii din departamentele 50 si 80 in perioada 1995-1999.

-- Sa se realizeze o operatie de modificare a pretului la produse astfel incat noul pret sa se micsoreze cu 5% pentru toate produsele care au cantitatea comandata mai mica decat cantitatea medie comandata din produsul cu denumirea care conţine CPU. (se actualizeaza tabela  rand_comenzi). La final sa se anuleze operatia de actualizare.

-- Sa se afiseze denumirea produselor si valoarea totala comandata a acestora (sum(cantitate*pret) cuprinsa intre 1500 si 4000.

-- Sa se afiseze numarul comenzii, data, valoarea totala (sum(cantitate*pret)), numarul de produse pentru comenzile online incheiate in perioada 1999-2000 si contin cel putin 2 produse

-- Sa se afiseze numarul comenzii, denumirea produsului, pretul, cantitatea si valoarea pentru produsele care contin in denumire cuvantul  Monitor.

-- Să se afişeze numele, id-ul departamentului si numărul de comenzi incheiate de angajatii din departamentul 80 in luna noiembrie. 

-- Sa se realizeze actualizarea pretului la produse astfel incat noul pret sa se micsoreze cu 10% pentru toate produsele care au pretul mai mare decat al pretul mediu al produsului cu id-ul ‘3155’ (se actualizeaza tabela  rand_comenzi). La final sa se anuleze actualizarea.

-- Sa se afiseze numele, denumirea functiei, numarul de comenzi pentru angajatii care au incheiat cel putin 2 comenzi.

-- Sa se realizeze actualizarea pretului la produse astfel incat noul pret sa se mareasca cu 5% pentru toate produsele care au valoarea comandata (cantitate*pret)  mai mare sau egala cu 1000 (se actualizeaza tabela  rand_comenzi). La final sa se anuleze operatia de actualizare

-- Sa se afiseze numele, numarul de comenzi, salariul si bonusul fiecarui angajat. Bonusul se va calcula in functie de numarul de comenzi incheiate, astfel:
--    intre 1-2 comenzi – 5% din salariul lunar;
--    intre 3-5 comenzi – 7% din salariul lunar;
--    mai mult de 5 comenzi – 10% din salariul lunar.