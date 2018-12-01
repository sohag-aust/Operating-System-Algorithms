package assignpc;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;
import java.util.Scanner;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;

class AssignPc {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the number of producer: ");
        int p = sc.nextInt();

        System.out.print("Enter the number of consumer: ");
        int c = sc.nextInt();

        System.out.println("\nStart Simulation->\n");

        Add add = new Add(p, c);

        for (int i = 0; i < p; i++) {
            Producer pro = new Producer(add, i + 1);
        }

        for (int i = 0; i < c; i++) {
            Consumer con = new Consumer(add, i + 1);
        }
    }
}

class Add {

    int p, c;
    Vector<Integer> que = new Vector<Integer>();

    int fullcount = 0;
    int emptycount = 0;
    int flag = 1;

    Add(int p, int c) {
        this.p = p;
        this.c = c;
        emptycount = this.p;
    }

    void put(int item, int id) {

        int sz = que.size();
        que.add(item);
        
        if (que.size() > sz) {
            emptycount--;
            System.out.println("Producer Empty spaces: " + emptycount);
            System.out.println("Producer " + id + ": Data " + item + " is inserted in the buffer.");
            fullcount++;
            System.out.println("Producer Full spaces: " + fullcount);
        }
     }

    void get(int id) {

        int val = que.get(id-1);
        System.out.println("\nConsumer " + id + ": Consumed Data " + val + " from the buffer.");

        fullcount--;
        emptycount++;

        System.out.println("Consumer Empty spaces: " + emptycount);
        System.out.println("Consumer Full spaces: " + fullcount);
    }
}

class Producer implements Runnable {

    Add add;
    int id;

    Producer(Add add, int id) {

        this.add = add;
        this.id = id;
        new Thread(this, "Producer P " + this.id).start();
    }

    public void run() {

        Scanner sc = new Scanner(System.in);
        Random rand = new Random();

        try {

            int val = rand.nextInt(20);
            System.out.println("\nProducer ->" + id + ": produces value " + val);
            add.put(val, id);

        } catch (Exception ex) {
            Logger.getLogger(Producer.class.getName()).log(Level.SEVERE, null, ex);
        }

        sc.close();
    }
}

class Consumer implements Runnable {

    Add add;
    int id;

    Consumer(Add add, int id) {

        this.add = add;
        this.id = id;
        new Thread(this, "Consumer C " + this.id).start();
    }

    public void run() {
        try {

            add.get(id);

        } catch (Exception ex) {
            Logger.getLogger(Consumer.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}