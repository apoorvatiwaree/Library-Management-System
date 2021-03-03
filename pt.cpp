#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
using namespace std;

class book
{
	char bno[6];
	char bname[30];
	char acode[10];
	public:
	void bcreate()
	{
        cout<<"\nNEW BOOK ENTRY";
        cout<<"\n\nEnter book code : ";
        cin>>bno;
        cout<<"\nEnter Name of The Book : ";
        cin.ignore();
        cin.getline(bname,29,'\n');
        cout<<"\nEnter Author Code : ";
        cin.getline(acode,9,'\n');
    }

    void show_book()
    {
        cout<<"\nBook code : "<<bno;
        cout<<"\nBook Name : ";
        puts(bname);
    }

    char* retbno()
    {
        return bno;
    }

    void report()
    {
        cout<<bno<<setw(30)<<bname<<setw(30)<<acode<<endl;
    }
};

class member
{
    char id[6];
    char mname[20];
    char mbno[6];
    int token;
    public:
    void mcreate()
    {
        cout<<"\n\n\tNEW MEMBER\nInformation once entered cannot be edited \nEnter id : ";
        cin>>id;
        cout<<"\n\nEnter Member name : ";
        cin.ignore();
        cin.getline(mname,19,'\n');
        token=0;
        mbno[0]='\0';
        cout<<"\n Registration is complete";
    }

    void showm()
    {
        cout<<"\n\nId : "<<id;
        cout<<"\nMember Name : ";
        puts(mname);
        cout<<"No of Book issued : "<<token;
        if(token==1)
           {
               cout<<"\nBook No "<<mbno;
           }
    }

    char* retmbno()
    {
        return mbno;
    }

    int rettoken()
    {
        return token;
    }

    void addtoken()
    {
        token=1;
    }

    void resettoken()
    {
        token=0;
    }

    void getmbno(char t[])
    {
        strcpy(mbno,t);
    }

    void report()
    {
        cout<<"\n\t"<<id<<setw(20)<<mname<<setw(10)<<token<<endl;
    }

};

fstream fp,fp1,fmes;
book b;
member m;

void display_allb()
{

    fp.open("book.dat",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
        return;
    }

    cout<<"\n\n\t\tBOOK LIST\n\n";
    cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";

    while(fp.read((char*)&b,sizeof(book)))
    {
        b.report();
    }
         fp.close();
}

void bissue()
{
    char sn[6],bn[6];
    int found=0,flag=0;

    cout<<"\n\nBOOK ISSUE ";

    display_allb();

    cout<<"\n\n\tEnter The member's id.";
    cin>>sn;
    fp.open("member.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&m,sizeof(member)) && found==0)
    {
        if(strcmp(m.retmbno(),sn)!=0)
        {
            found=1;
            if(m.rettoken()==0)
            {
                cout<<"\n\n\tEnter the book no. ";
                cin>>bn;
                while(fp1.read((char*)&b,sizeof(book))&& flag==0)
                {
                    if(strcmp(b.retbno(),bn)==0)
                    {
                        b.show_book();

                        flag=1;
                        m.addtoken();
                        m.getmbno(b.retbno());

                        int pos=-1*sizeof(m);
                        fp.seekp(pos,ios::cur);

                        fp.write((char*)&m,sizeof(member));

                        cout<<"\n\n\t Book issued \nNote: Return within 15 days \nFine: Rs. 50 per day after expiry period";
                    }
                }
                if(flag==0)
                {
                      cout<<"Book no does not exist";
                }

            }
            else
            {
                cout<<"You have not returned the last book ";
            }

        }
    }
    if(found==0)
    {
        cout<<"Member record not exist";
    }

    fp.close();
    fp1.close();
}

void breturn()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;

    cout<<"\n\nBOOK RETURN.";
    cout<<"\n\n\tEnter The member id.";
    cin>>sn;
    fp.open("member.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&m,sizeof(member)) && found==0)
    {
        if(strcmp(m.retmbno(),sn)!=0)
        {
            found=1;
            if(m.rettoken()==1)
            {
            while(fp1.read((char*)&b,sizeof(book))&& flag==0)
            {
            if(strcmp(b.retbno(),m.retmbno())==0)
            {
                b.show_book();

                flag=1;
                cout<<"\n\nBook deposited in no. of days : ";
                cin>>day;
                if(day>15)
                {
                   fine=(day-15)*50;
                   cout<<"\n\nFine has to deposited Rs. "<<fine;
                }
                    m.resettoken();
                    int pos=-1*sizeof(m);
                    fp.seekp(pos,ios::cur);
                    fp.write((char*)&m,sizeof(member));
                    cout<<"\n\n\t Book deposited successfully";
            }
            }
            if(flag==0)
            {
                cout<<"Book no does not exist";
            }
            }
            else
            {
               cout<<"No book is issued";
            }
        }
    }
    if(found==0)
    {
        cout<<"\nMember record does not exist";
    }
    fp.close();
    fp1.close();
  }

void bmodify ()
{
    char n[6];
    int found=0;

    cout<<"\n\n\tMODIFY BOOK REOCORD ";
    cout<<"\n\n\tEnter book code : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&b,sizeof(book)) && found==0)
    {
        if(strcmp(b.retbno(),n)==0)
        {
            b.show_book();
            cout<<"\nEnter New Details of book : ";
            b.bcreate();

            int pos=-1*sizeof(b);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&b,sizeof(book));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }
    fp.close();
    if(found==0)
    {
        cout<<"\nRecord not found ";
    }
}
void bdelete()
{
    char n[6];

    cout<<"\n\n\n\tDELETE BOOK ";
    cout<<"\n\nEnter The Book no. : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&b,sizeof(book)))
    {
        if(strcmp(b.retbno(),n)!=0)
        {
            fp2.write((char*)&b,sizeof(book));
        }
    }
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat","book.dat");
    cout<<"\n\tRecord Deleted ..";

}



void bwrite()
{
    char ch;
    fp.open("book.dat",ios::out|ios::app);
    do
    {
        b.bcreate();
        fp.write((char*)&b,sizeof(book));
        cout<<"\n\nDo you want to add more record..(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}

void mwrite()
{
    char ch;
    fp.open("member.dat",ios::out|ios::app);

    do
    {
        m.mcreate();
        fp.write((char*)&m,sizeof(member));
        cout<<"\n\ndo you want to add more record..(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');

    fp.close();
}

void display_spb(char n[])
{
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&b,sizeof(book)))
    {
        if(strcmp(b.retbno(),n)==0)
        {
            b.show_book();
             flag=1;
        }
    }

    fp.close();

    if(flag==0)
    {
        cout<<"\n\nBook does not exist";
    }
}

void display_sps(char n[])
{
    cout<<"\nMEMBER DETAILS\n";
    int flag=0;
    fp.open("member.dat",ios::in);
    while(fp.read((char*)&m,sizeof(member)))
    {
        if((strcmp(m.retmbno(),n)==0))
        {
            m.showm();
            flag=1;
        }
    }

    fp.close();
    if(flag==0)
    {
        cout<<"\n\nMember does not exist";
    }
}

void mshow()
{
    fp.open("member.dat",ios::in);

    while(fp.read((char*)&m,sizeof(member)))
    {
        m.showm();
    }

    fp.close();

}
void mdelete()
{
    char n[6];
    int flag=0;

    cout<<"\n\n\n\tDELETE MEMBER";
    cout<<"\n\nEnter The id. of the Member You Want To Delete : ";
    cin>>n;
    fp.open("member.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&m,sizeof(member)))
    {
        if(strcmp(m.retmbno(),n)!=0)
        {
            fp2.write((char*)&m,sizeof(member));
        }
        else
        {
            flag=1;
        }
    }

    fp2.close();
    fp.close();
    remove("member.dat");
    rename("Temp.dat","member.dat");
    if(flag==1)
    {
        cout<<"\n\n\tRecord Deleted ";
    }
    else
    {
        cout<<"\n\nRecord not found";
    }
}

class message
{
    char n[20];
    char message[50];
public:
    void leavem()
    {
        cout<<"\nName:";
        cin.ignore();
        cin.getline(n,19,'\n');
        cout<<"\nMessage (max 50 char):";
        cin.getline(message,49,'\n');
    }
    void showmes()
    {
        cout<<n<<" : "<<message;
    }
};

message mes;

void leavemm()
{
    mes.leavem();
    fmes.open("message.dat",ios::in|ios::out);
    fmes.write((char*)&mes,sizeof(mes));
}
void showmess()
{
    fmes.open("message.dat",ios::in);
    fmes.read((char*)&mes,sizeof(mes));
    mes.showmes();
}

void Librarian_menu()
{
    int chh;
    do
    {
    cout<<"\n\nLIBRARIAN MENU";
    cout<<"\n\t1.Display messages\t\t\t2.Create member record\t\t\t6.Create book record\n\t\t\t\t\t\t3.Display specific member record\t7.Display all books\n\t\t\t\t\t\t4. Show all members\t\t\t8.Display specific book\n\t\t\t\t\t\t5.Delete member record\t\t\t9.Modify book record \n\t\t\t\t\t\t\t\t\t\t\t10.Delete book record \n\t11.EXIT  ";
    cin>>chh;
    switch(chh)
    {
        case 1:
           showmess();
        break;
        case 2:
            mwrite();
        break;
        case 3:
            char num[6];

            cout<<"\n\n\tPlease Enter The Id. ";
            cin>>num;
            display_sps(num);
        break;
        case 4:
            mshow();
        break;
        case 5:
             mdelete ();
        break;
        case 6:
            bwrite();
        break;
        case 7:
            display_allb();
        break;
        case 8:
             {
                char num[6];
                cout<<"\n\n\tPlease Enter The book No. ";
                cin>>num;
                display_spb(num);
                break;
            }
        case 9:
            bmodify();
        break;
        case 10:
             bdelete ();
        break;
        case 11:
            return;
        default:
            cout<<"\ERROR";
       }
    }while(chh!=11);
}

int main()
{
    int ch;
    int pass;
    cout<<"\n\t\t\tLIBRARY MANAGEMENT SYSTEM";
    cout<<"\n\n1.For Members\t\t2.For Librarians\t\t3.Leave a message\n";
    cin>>ch;
    switch(ch)
    {
    case 1:
        cout<<"\n\t\t\tMEMBER MENU\n\n1. Issue a book\t\t\t\t2. Return a book\n3.EXIT ";
        cin>>ch;
        switch(ch)
          {
            case 1:
                bissue();
            break;
            case 2:
                breturn();
            break;
            default:
                cout<<"INVALID";
          }
    break;
    case 2:
        cout<<"\n\t\t\t\tEnter password : ";
        cin>>pass;
        if(pass==110085)
            {
                Librarian_menu();
            }
        else
            {
                cout<<"\nWRONG PASSWORD";
            }
    break;
    case 3:
        leavemm();

    break;
    default:
            cout<<"\nINVALID";
    }
}


