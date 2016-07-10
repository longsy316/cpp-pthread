//
//  read_write_lock.hpp
//  read_write_lock
//
//  Created by herbert koelman on 18/03/2016.
//
//

#ifndef pthread_read_write_lock_hpp
#define pthread_read_write_lock_hpp

// must be include as first hearder file of each source code file (see IBM's
// recommandation for more info p.285 §8.3.1).
#include <pthread.h>

#include "pthread/config.h"
#include "pthread/exceptions.hpp"


namespace pthread {
  
  /** \addtogroup concurrency
   *
   * @{
   */

  /** This class acquires the read lock
   *
   * @author herbert koelman (herbert.koelman@me.com)
   * @since v1.6.0
   */
  class read_lock {
    public:

      /** The method apply a read lock.
       *
       * The calling thread acquires the write lock if no other thread (reader or writer) holds the read-write lock. Otherwise, the thread shall block until
       * it can acquire the lock. The calling thread may deadlock if at the time the call is made it holds the read-write lock (whether a read or write lock).
       */
      void lock ();
      
      /** The method shall apply a read lock, if any thread currently holds the lock (for reading or writing) 
       * the method throws an exception.
       *
       @see lock
       */
      void try_lock ();
      
      /** release the read lock.
       @throw read_write_lock_exception if error conditions preventing this method to succeed.
       */
      void unlock ();
      
      /**
       Constructor/Desctructor

       this constructor shall allocate any resources required to use the read-write lock referenced by rwlock and initializes the lock to an unlocked state. The read/write lock
       passes NULL attributes. This means default behavior.

       @throw read_write_lock_exception if error conditions preventing this method to succeed.
       */
       read_lock ();

      /**
       * the descructor, shall destroy the read-write lock object referenced by rwlock and release any resources used by the lock.
       */
       virtual ~read_lock ();

    protected:

      /** read/write lock reference */
      pthread_rwlock_t _rwlock;
  };

  /** This class acquires the read/write write lock
   *
   * @author herbert koelman (herbert.koelman@me.com)
   * @since v1.6.0
   */
  class write_lock: public read_lock {
    public:
      /** The method apply a write lock.
       *
       * The calling thread acquires the write lock if no other thread (reader or writer) holds the read-write lock. Otherwise, the thread shall block until
       * it can acquire the lock. The calling thread may deadlock if at the time the call is made it holds the read-write lock (whether a read or write lock).
       */
      void lock ();
      
      /** The method shall apply a write lock, if any thread currently holds the lock (for reading or writing) 
       * the method throws an exception.
       *
       @see lock
       */
      void try_lock ();
      
      /**
       Constructor/Desctructor

       this constructor shall allocate any resources required to use the read-write lock referenced by rwlock and initializes the lock to an unlocked state. The read/write lock
       passes NULL attributes. This means default behavior.

       @throw read_write_lock_exception if error conditions preventing this method to succeed.
       */
       write_lock ();

      /**
       * the descructor, shall destroy the read-write lock object referenced by rwlock and release any resources used by the lock.
       */
      virtual ~write_lock ();

  };

  /** A read/write lock.
   *
   * <pre><code>
   * ...
   * pthread::read_write_lock _rwlock;
   *
   * {
   *   // get a read lock
   *   pthread::lock_guard<pthread::read_lock> lock(_rwlck);
   *   ...
   * } // lock_guard unlock lock here
   *
   * {
   *   // get write lock
   *   pthread::lock_guard<pthread::write_lock> lock(_rwlck);
   *   ...
   * } // lock_guard unlock lock here
   *
   * </code></pre>
   *
   */
  typedef write_lock read_write_lock;
  
  /** @} */
} // namespace pthread

#endif /* pthread_read_write_lock_H */
